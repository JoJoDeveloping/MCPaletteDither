# MCPaletteDither
Dithers the MC palette, or any palette

# How to access the palette
It's zipped and stored in `palette.zip`. See `Ditherer.java` for it's layout.

## Why?
Minecraft is a game made by Mojang. In there, there are maps which can be used to display arbitrary images. Unfortunately these images are constrained by a palette of usable colors, which at the time of writing contains 204 entries.
It's an accepted solution to dither colors in order to get the human eye to perceive more colors than there actually are. For more information on dithering, see [Numberphile's videos on them](https://www.youtube.com/watch?v=IviNO7iICTM&t=383s).
I needed a solution that is both fast and in-place / runnable on a GPU. So I came up with this palette-based approach. Since there are only about 16 million colors, and modern GPUs have a multiple of that as available memory, we can save some of that to store a table telling us which RGB colors maps to which palette colors in what order.

## What algorithm is used
This algorithm is based on and adapted from [Yliluoma's ordered dithering algorithm](https://bisqwit.iki.fi/story/howto/dither/jy/). A short description is:
1. convert the entire palette into XYZ and DIN99 colorspace. XYZ is chosen because it's a linear transformation of RGB colorspace, and RGB colorspace is the space where color mixing has to take place so that the mix result accurately reflects the color perceived when two pixels are placed right next to each other. Since XYZ is just a linear transformation of that, the same holds for it. DIN99 is chosen because it allows for easy but accurate (more accurate than LAB dE 76) color comparsion.
2. Find all edges between two palette entries (in following called vertices) that are below a certain length (I chose 37 here because that's what I came up with after some experimentation) and don't have a color lying directly inbetween them (this ensures we have edges black-gray and gray-white but not black-white, since gray already lies on the line black-white)
3. Find all 4D polygons (pyramids) that can be made from the edges above. Compute an inversion matrix that maps a point into the coordinate system whose basis vectors are the edge vectors of the polygon sharing a common point. This allows us to later easily construct how you would have to mix the colors to archieve the desired color.
4. For all RGB colors, find the color closest to it that is one of the following:
4.1. One of the base vertices
4.2. On an allowed line as descibed above
4.3. Inside the polygon created by four vertices as descibed above
5. Store the result of that for all RGB colors for later use
6. To dither an image, look up the used colors in the RGB table.

Steps 1..3 are handled by the python script, Step 4 is in OpenGL, Step 5 is in C++, and Step 6 is left to the reader.

### On colorspaces
One might think that we can compute the closest point on the line using linear algebra. The problem with that approach is that we determine the distance between two colors using the DIN colorspace, while the line, having abstracted all possible mixtures of two RGB pixels on a screen, is only a line in RGB colorspace. Since the transformation from RGB to DIN is nonlinear, the line ends up being curve. Finding the nearest point on an arbitrary curve is nontrivial.

Similarly, the same problem exists for triangles, or the mixing product of three vertices. While we can more or less effectively step along each line between two vertices, we can't step all over the plane spanned by three vertices, since there's about 100 times as many triangles as there are lines and we would have to step over 32 times as many points.

This does not apply to 4-vertix polygons. If a point is in them, the error is 0 since we can exactly reach that point by appropiately mixing the colors together. Therefore we don't need to compute color distances here, so we can stay within RGB (or XYZ) colorspace. This means however that poins outside a polygon will not be projected on the polygon's face.

## On the code
The code in here was 'quickly' hacked together over the course of a week. Don't expect it to work on your machine. It's supposed to do one job, which it does, while staying easily hackable.

Most importantly, the fragment shader runs for 17 seconds on my machine (GTX 1060M). On Linux, you can modify the Xorg config file to tell the NVidia driver to not kill shaders when they run for longer than a few seconds - google "nvidia xorg interactive". I don't know whether this is possible on Linux.

The whole program took about 2 hours on my machine. To prevent your graphics card from overheating, you might want to pause the program (`kill -STOP <pid>`) from time to time.

This code is somewhat good at producing random driver bugs. Be warned when running this.

Link this with `-lOpenGL -lGLEW -lEGL -lglut`


# Credits
This code includes lodepng made by Lode Vandevenne. Get it here: https://lodev.org/lodepng/

It also contains the Minecraft 1.12.2 color palette.
