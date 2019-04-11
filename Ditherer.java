import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

public class Ditherer {

    private RandomAccessFile raf;
    private MappedByteBuffer mbb;

    private int[] bayerMatrix = new int[]{
            0,   32,    8,   40,    2,   34,   10,   42,
            48,   16,   56,   24,   50,   18,   58,   26,
            12,   44,    4,   36,   14,   46,    6,   38,
            60,   28,   52,   20,   62,   30,   54,   22,
            3,   35,   11,   43,    1,   33,    9,   41,
            51,   19,   59,   27,   49,   17,   57,   25,
            15,   47,    7,   39,   13,   45,    5,   37,
            63,   31,   55,   23,   61,   29,   53,   21};

    public Ditherer(File mapdir) throws IOException {
        raf = new RandomAccessFile(new File(mapdir, "palette.bin"), "r");
        mbb = raf.getChannel().map(FileChannel.MapMode.READ_ONLY, 0, raf.length());
        mbb.load();
        if(raf.length()!=256*256*256*8)
            throw new IOException("Invalid palette!");
    }


    public void ditherOnto(BufferedImage image, byte[] imageData) {
        for(int x = 0; x < image.getWidth(); x++)
            for(int y = 0; y < image.getHeight(); y++){
                int color = image.getRGB(x, y);
                int blue = color & 0xff;
                int green = (color & 0xff00) >> 8;
                int red = (color & 0xff0000) >> 16;
                int rcol = (red | (green<<8) | (blue<<16))*4;
                byte res;
                int cutoff = bayerMatrix[(x%8)*8+y%8];
                if(cutoff <= mbb.get(rcol+256*256*256*4))
                    res= mbb.get(rcol);
                else if(cutoff <= mbb.get(rcol+256*256*256*4+1))
                    res = mbb.get(rcol+1);
                else if(cutoff <= mbb.get(rcol+256*256*256*4+2))
                    res = mbb.get(rcol+2);
                else
                    res = mbb.get(rcol+3);
                imageData[image.getWidth()*y+x]= res;
            }
    }
}
