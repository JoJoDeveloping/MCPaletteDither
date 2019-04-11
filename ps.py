import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from scipy.spatial import Delaunay
from itertools import *
from math import pow,log,pi,e,sin,cos,sqrt
import struct
import os

def c(a,b,x):return (a,b,x)
rawpoints = np.array([c(89, 125, 39), c(109, 153, 48), c(127, 178, 56), c(67, 94, 29), c(174, 164, 115), c(213, 201, 140), c(247, 233, 163), c(130, 123, 86), c(140, 140, 140), c(171, 171, 171), c(199, 199, 199), c(105, 105, 105), c(180, 0, 0), c(220, 0, 0), c(255, 0, 0), c(135, 0, 0), c(112, 112, 180), c(138, 138, 220), c(160, 160, 255), c(84, 84, 135), c(117, 117, 117), c(144, 144, 144), c(167, 167, 167), c(88, 88, 88), c(0, 87, 0), c(0, 106, 0), c(0, 124, 0), c(0, 65, 0), c(180, 180, 180), c(220, 220, 220), c(255, 255, 255), c(135, 135, 135), c(115, 118, 129), c(141, 144, 158), c(164, 168, 184), c(86, 88, 97), c(106, 76, 54), c(130, 94, 66), c(151, 109, 77), c(79, 57, 40), c(79, 79, 79), c(96, 96, 96), c(112, 112, 112), c(59, 59, 59), c(45, 45, 180), c(55, 55, 220), c(64, 64, 255), c(33, 33, 135), c(100, 84, 50), c(123, 102, 62), c(143, 119, 72), c(75, 63, 38), c(180, 177, 172), c(220, 217, 211), c(255, 252, 245), c(135, 133, 129), c(152, 89, 36), c(186, 109, 44), c(216, 127, 51), c(114, 67, 27), c(125, 53, 152), c(153, 65, 186), c(178, 76, 216), c(94, 40, 114), c(72, 108, 152), c(88, 132, 186), c(102, 153, 216), c(54, 81, 114), c(161, 161, 36), c(197, 197, 44), c(229, 229, 51), c(121, 121, 27), c(89, 144, 17), c(109, 176, 21), c(127, 204, 25), c(67, 108, 13), c(170, 89, 116), c(208, 109, 142), c(242, 127, 165), c(128, 67, 87), c(53, 53, 53), c(65, 65, 65), c(76, 76, 76), c(40, 40, 40), c(108, 108, 108), c(132, 132, 132), c(153, 153, 153), c(81, 81, 81), c(53, 89, 108), c(65, 109, 132), c(76, 127, 153), c(40, 67, 81), c(89, 44, 125), c(109, 54, 153), c(127, 63, 178), c(67, 33, 94), c(36, 53, 125), c(44, 65, 153), c(51, 76, 178), c(27, 40, 94), c(72, 53, 36), c(88, 65, 44), c(102, 76, 51), c(54, 40, 27), c(72, 89, 36), c(88, 109, 44), c(102, 127, 51), c(54, 67, 27), c(108, 36, 36), c(132, 44, 44), c(153, 51, 51), c(81, 27, 27), c(17, 17, 17), c(21, 21, 21), c(25, 25, 25), c(13, 13, 13), c(176, 168, 54), c(215, 205, 66), c(250, 238, 77), c(132, 126, 40), c(64, 154, 150), c(79, 188, 183), c(92, 219, 213), c(48, 115, 112), c(52, 90, 180), c(63, 110, 220), c(74, 128, 255), c(39, 67, 135), c(0, 153, 40), c(0, 187, 50), c(0, 217, 58), c(0, 114, 30), c(91, 60, 34), c(111, 74, 42), c(129, 86, 49), c(68, 45, 25), c(79, 1, 0), c(96, 1, 0), c(112, 2, 0), c(59, 1, 0), c(147, 124, 113), c(180, 152, 138), c(209, 177, 161), c(110, 93, 85), c(112, 57, 25), c(137, 70, 31), c(159, 82, 36), c(84, 43, 19), c(105, 61, 76), c(128, 75, 93), c(149, 87, 108), c(78, 46, 57), c(79, 76, 97), c(96, 93, 119), c(112, 108, 138), c(59, 57, 73), c(131, 93, 25), c(160, 114, 31), c(186, 133, 36), c(98, 70, 19), c(72, 82, 37), c(88, 100, 45), c(103, 117, 53), c(54, 61, 28), c(112, 54, 55), c(138, 66, 67), c(160, 77, 78), c(84, 40, 41), c(40, 28, 24), c(49, 35, 30), c(57, 41, 35), c(30, 21, 18), c(95, 75, 69), c(116, 92, 84), c(135, 107, 98), c(71, 56, 51), c(61, 64, 64), c(75, 79, 79), c(87, 92, 92), c(46, 48, 48), c(86, 51, 62), c(105, 62, 75), c(122, 73, 88), c(64, 38, 46), c(53, 43, 64), c(65, 53, 79), c(76, 62, 92), c(40, 32, 48), c(53, 35, 24), c(65, 43, 30), c(76, 50, 35), c(40, 26, 18), c(53, 57, 29), c(65, 70, 36), c(76, 82, 42), c(40, 43, 22), c(100, 42, 32), c(122, 51, 39), c(142, 60, 46), c(75, 31, 24), c(26, 15, 11), c(31, 18, 13), c(37, 22, 16), c(19, 11, 8)])

def rgbdin(r,g,b):
    r/=255.
    b/=255.
    g/=255.
    r = pow((r + 0.055) / 1.055, 2.4) if r > 0.04045 else r / 12.92
    g = pow((g + 0.055) / 1.055, 2.4) if g > 0.04045 else g / 12.92
    b = pow((b + 0.055) / 1.055, 2.4) if b > 0.04045 else b / 12.92
    x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 0.95047
    y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 1.00000
    z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 1.08883
    return x,y,z

xyzpoints = np.array([rgbdin(89, 125, 39), rgbdin(109, 153, 48), rgbdin(127, 178, 56), rgbdin(67, 94, 29), rgbdin(174, 164, 115), rgbdin(213, 201, 140), rgbdin(247, 233, 163), rgbdin(130, 123, 86), rgbdin(140, 140, 140), rgbdin(171, 171, 171), rgbdin(199, 199, 199), rgbdin(105, 105, 105), rgbdin(180, 0, 0), rgbdin(220, 0, 0), rgbdin(255, 0, 0), rgbdin(135, 0, 0), rgbdin(112, 112, 180), rgbdin(138, 138, 220), rgbdin(160, 160, 255), rgbdin(84, 84, 135), rgbdin(117, 117, 117), rgbdin(144, 144, 144), rgbdin(167, 167, 167), rgbdin(88, 88, 88), rgbdin(0, 87, 0), rgbdin(0, 106, 0), rgbdin(0, 124, 0), rgbdin(0, 65, 0), rgbdin(180, 180, 180), rgbdin(220, 220, 220), rgbdin(255, 255, 255), rgbdin(135, 135, 135), rgbdin(115, 118, 129), rgbdin(141, 144, 158), rgbdin(164, 168, 184), rgbdin(86, 88, 97), rgbdin(106, 76, 54), rgbdin(130, 94, 66), rgbdin(151, 109, 77), rgbdin(79, 57, 40), rgbdin(79, 79, 79), rgbdin(96, 96, 96), rgbdin(112, 112, 112), rgbdin(59, 59, 59), rgbdin(45, 45, 180), rgbdin(55, 55, 220), rgbdin(64, 64, 255), rgbdin(33, 33, 135), rgbdin(100, 84, 50), rgbdin(123, 102, 62), rgbdin(143, 119, 72), rgbdin(75, 63, 38), rgbdin(180, 177, 172), rgbdin(220, 217, 211), rgbdin(255, 252, 245), rgbdin(135, 133, 129), rgbdin(152, 89, 36), rgbdin(186, 109, 44), rgbdin(216, 127, 51), rgbdin(114, 67, 27), rgbdin(125, 53, 152), rgbdin(153, 65, 186), rgbdin(178, 76, 216), rgbdin(94, 40, 114), rgbdin(72, 108, 152), rgbdin(88, 132, 186), rgbdin(102, 153, 216), rgbdin(54, 81, 114), rgbdin(161, 161, 36), rgbdin(197, 197, 44), rgbdin(229, 229, 51), rgbdin(121, 121, 27), rgbdin(89, 144, 17), rgbdin(109, 176, 21), rgbdin(127, 204, 25), rgbdin(67, 108, 13), rgbdin(170, 89, 116), rgbdin(208, 109, 142), rgbdin(242, 127, 165), rgbdin(128, 67, 87), rgbdin(53, 53, 53), rgbdin(65, 65, 65), rgbdin(76, 76, 76), rgbdin(40, 40, 40), rgbdin(108, 108, 108), rgbdin(132, 132, 132), rgbdin(153, 153, 153), rgbdin(81, 81, 81), rgbdin(53, 89, 108), rgbdin(65, 109, 132), rgbdin(76, 127, 153), rgbdin(40, 67, 81), rgbdin(89, 44, 125), rgbdin(109, 54, 153), rgbdin(127, 63, 178), rgbdin(67, 33, 94), rgbdin(36, 53, 125), rgbdin(44, 65, 153), rgbdin(51, 76, 178), rgbdin(27, 40, 94), rgbdin(72, 53, 36), rgbdin(88, 65, 44), rgbdin(102, 76, 51), rgbdin(54, 40, 27), rgbdin(72, 89, 36), rgbdin(88, 109, 44), rgbdin(102, 127, 51), rgbdin(54, 67, 27), rgbdin(108, 36, 36), rgbdin(132, 44, 44), rgbdin(153, 51, 51), rgbdin(81, 27, 27), rgbdin(17, 17, 17), rgbdin(21, 21, 21), rgbdin(25, 25, 25), rgbdin(13, 13, 13), rgbdin(176, 168, 54), rgbdin(215, 205, 66), rgbdin(250, 238, 77), rgbdin(132, 126, 40), rgbdin(64, 154, 150), rgbdin(79, 188, 183), rgbdin(92, 219, 213), rgbdin(48, 115, 112), rgbdin(52, 90, 180), rgbdin(63, 110, 220), rgbdin(74, 128, 255), rgbdin(39, 67, 135), rgbdin(0, 153, 40), rgbdin(0, 187, 50), rgbdin(0, 217, 58), rgbdin(0, 114, 30), rgbdin(91, 60, 34), rgbdin(111, 74, 42), rgbdin(129, 86, 49), rgbdin(68, 45, 25), rgbdin(79, 1, 0), rgbdin(96, 1, 0), rgbdin(112, 2, 0), rgbdin(59, 1, 0), rgbdin(147, 124, 113), rgbdin(180, 152, 138), rgbdin(209, 177, 161), rgbdin(110, 93, 85), rgbdin(112, 57, 25), rgbdin(137, 70, 31), rgbdin(159, 82, 36), rgbdin(84, 43, 19), rgbdin(105, 61, 76), rgbdin(128, 75, 93), rgbdin(149, 87, 108), rgbdin(78, 46, 57), rgbdin(79, 76, 97), rgbdin(96, 93, 119), rgbdin(112, 108, 138), rgbdin(59, 57, 73), rgbdin(131, 93, 25), rgbdin(160, 114, 31), rgbdin(186, 133, 36), rgbdin(98, 70, 19), rgbdin(72, 82, 37), rgbdin(88, 100, 45), rgbdin(103, 117, 53), rgbdin(54, 61, 28), rgbdin(112, 54, 55), rgbdin(138, 66, 67), rgbdin(160, 77, 78), rgbdin(84, 40, 41), rgbdin(40, 28, 24), rgbdin(49, 35, 30), rgbdin(57, 41, 35), rgbdin(30, 21, 18), rgbdin(95, 75, 69), rgbdin(116, 92, 84), rgbdin(135, 107, 98), rgbdin(71, 56, 51), rgbdin(61, 64, 64), rgbdin(75, 79, 79), rgbdin(87, 92, 92), rgbdin(46, 48, 48), rgbdin(86, 51, 62), rgbdin(105, 62, 75), rgbdin(122, 73, 88), rgbdin(64, 38, 46), rgbdin(53, 43, 64), rgbdin(65, 53, 79), rgbdin(76, 62, 92), rgbdin(40, 32, 48), rgbdin(53, 35, 24), rgbdin(65, 43, 30), rgbdin(76, 50, 35), rgbdin(40, 26, 18), rgbdin(53, 57, 29), rgbdin(65, 70, 36), rgbdin(76, 82, 42), rgbdin(40, 43, 22), rgbdin(100, 42, 32), rgbdin(122, 51, 39), rgbdin(142, 60, 46), rgbdin(75, 31, 24), rgbdin(26, 15, 11), rgbdin(31, 18, 13), rgbdin(37, 22, 16), rgbdin(19, 11, 8)])


def rgbdin(r,g,b):
    r/=255.
    b/=255.
    g/=255.
    r = pow((r + 0.055) / 1.055, 2.4) if r > 0.04045 else r / 12.92
    g = pow((g + 0.055) / 1.055, 2.4) if g > 0.04045 else g / 12.92
    b = pow((b + 0.055) / 1.055, 2.4) if b > 0.04045 else b / 12.92
    x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 0.95047
    y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 1.00000
    z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 1.08883
    x = pow(x, 1./3.) if x > 0.008856 else (7.787 * x) + 16./116.
    y = pow(y, 1./3.) if y > 0.008856 else (7.787 * y) + 16./116.
    z = pow(z, 1./3.) if z > 0.008856 else (7.787 * z) + 16./116.
    L,a,b = (116*y -16, 500*(x-y), 200*(y-z))
    L99 = 105.51 * log(1+0.0158*L)
    e99 = a*cos(16*pi/180)+b*sin(16*pi/180)
    f = 0.7*(-a*sin(16*pi/180)+b*cos(16*pi/180))
    G = (e99*e99+f*f)**0.5
    k=log(1+0.045*G)/0.045
    a99 = k*e99/G
    b99 = k*f/G
    return L99, a99, b99
dinpoints = np.array([rgbdin(89, 125, 39), rgbdin(109, 153, 48), rgbdin(127, 178, 56), rgbdin(67, 94, 29), rgbdin(174, 164, 115), rgbdin(213, 201, 140), rgbdin(247, 233, 163), rgbdin(130, 123, 86), rgbdin(140, 140, 140), rgbdin(171, 171, 171), rgbdin(199, 199, 199), rgbdin(105, 105, 105), rgbdin(180, 0, 0), rgbdin(220, 0, 0), rgbdin(255, 0, 0), rgbdin(135, 0, 0), rgbdin(112, 112, 180), rgbdin(138, 138, 220), rgbdin(160, 160, 255), rgbdin(84, 84, 135), rgbdin(117, 117, 117), rgbdin(144, 144, 144), rgbdin(167, 167, 167), rgbdin(88, 88, 88), rgbdin(0, 87, 0), rgbdin(0, 106, 0), rgbdin(0, 124, 0), rgbdin(0, 65, 0), rgbdin(180, 180, 180), rgbdin(220, 220, 220), rgbdin(255, 255, 255), rgbdin(135, 135, 135), rgbdin(115, 118, 129), rgbdin(141, 144, 158), rgbdin(164, 168, 184), rgbdin(86, 88, 97), rgbdin(106, 76, 54), rgbdin(130, 94, 66), rgbdin(151, 109, 77), rgbdin(79, 57, 40), rgbdin(79, 79, 79), rgbdin(96, 96, 96), rgbdin(112, 112, 112), rgbdin(59, 59, 59), rgbdin(45, 45, 180), rgbdin(55, 55, 220), rgbdin(64, 64, 255), rgbdin(33, 33, 135), rgbdin(100, 84, 50), rgbdin(123, 102, 62), rgbdin(143, 119, 72), rgbdin(75, 63, 38), rgbdin(180, 177, 172), rgbdin(220, 217, 211), rgbdin(255, 252, 245), rgbdin(135, 133, 129), rgbdin(152, 89, 36), rgbdin(186, 109, 44), rgbdin(216, 127, 51), rgbdin(114, 67, 27), rgbdin(125, 53, 152), rgbdin(153, 65, 186), rgbdin(178, 76, 216), rgbdin(94, 40, 114), rgbdin(72, 108, 152), rgbdin(88, 132, 186), rgbdin(102, 153, 216), rgbdin(54, 81, 114), rgbdin(161, 161, 36), rgbdin(197, 197, 44), rgbdin(229, 229, 51), rgbdin(121, 121, 27), rgbdin(89, 144, 17), rgbdin(109, 176, 21), rgbdin(127, 204, 25), rgbdin(67, 108, 13), rgbdin(170, 89, 116), rgbdin(208, 109, 142), rgbdin(242, 127, 165), rgbdin(128, 67, 87), rgbdin(53, 53, 53), rgbdin(65, 65, 65), rgbdin(76, 76, 76), rgbdin(40, 40, 40), rgbdin(108, 108, 108), rgbdin(132, 132, 132), rgbdin(153, 153, 153), rgbdin(81, 81, 81), rgbdin(53, 89, 108), rgbdin(65, 109, 132), rgbdin(76, 127, 153), rgbdin(40, 67, 81), rgbdin(89, 44, 125), rgbdin(109, 54, 153), rgbdin(127, 63, 178), rgbdin(67, 33, 94), rgbdin(36, 53, 125), rgbdin(44, 65, 153), rgbdin(51, 76, 178), rgbdin(27, 40, 94), rgbdin(72, 53, 36), rgbdin(88, 65, 44), rgbdin(102, 76, 51), rgbdin(54, 40, 27), rgbdin(72, 89, 36), rgbdin(88, 109, 44), rgbdin(102, 127, 51), rgbdin(54, 67, 27), rgbdin(108, 36, 36), rgbdin(132, 44, 44), rgbdin(153, 51, 51), rgbdin(81, 27, 27), rgbdin(17, 17, 17), rgbdin(21, 21, 21), rgbdin(25, 25, 25), rgbdin(13, 13, 13), rgbdin(176, 168, 54), rgbdin(215, 205, 66), rgbdin(250, 238, 77), rgbdin(132, 126, 40), rgbdin(64, 154, 150), rgbdin(79, 188, 183), rgbdin(92, 219, 213), rgbdin(48, 115, 112), rgbdin(52, 90, 180), rgbdin(63, 110, 220), rgbdin(74, 128, 255), rgbdin(39, 67, 135), rgbdin(0, 153, 40), rgbdin(0, 187, 50), rgbdin(0, 217, 58), rgbdin(0, 114, 30), rgbdin(91, 60, 34), rgbdin(111, 74, 42), rgbdin(129, 86, 49), rgbdin(68, 45, 25), rgbdin(79, 1, 0), rgbdin(96, 1, 0), rgbdin(112, 2, 0), rgbdin(59, 1, 0), rgbdin(147, 124, 113), rgbdin(180, 152, 138), rgbdin(209, 177, 161), rgbdin(110, 93, 85), rgbdin(112, 57, 25), rgbdin(137, 70, 31), rgbdin(159, 82, 36), rgbdin(84, 43, 19), rgbdin(105, 61, 76), rgbdin(128, 75, 93), rgbdin(149, 87, 108), rgbdin(78, 46, 57), rgbdin(79, 76, 97), rgbdin(96, 93, 119), rgbdin(112, 108, 138), rgbdin(59, 57, 73), rgbdin(131, 93, 25), rgbdin(160, 114, 31), rgbdin(186, 133, 36), rgbdin(98, 70, 19), rgbdin(72, 82, 37), rgbdin(88, 100, 45), rgbdin(103, 117, 53), rgbdin(54, 61, 28), rgbdin(112, 54, 55), rgbdin(138, 66, 67), rgbdin(160, 77, 78), rgbdin(84, 40, 41), rgbdin(40, 28, 24), rgbdin(49, 35, 30), rgbdin(57, 41, 35), rgbdin(30, 21, 18), rgbdin(95, 75, 69), rgbdin(116, 92, 84), rgbdin(135, 107, 98), rgbdin(71, 56, 51), rgbdin(61, 64, 64), rgbdin(75, 79, 79), rgbdin(87, 92, 92), rgbdin(46, 48, 48), rgbdin(86, 51, 62), rgbdin(105, 62, 75), rgbdin(122, 73, 88), rgbdin(64, 38, 46), rgbdin(53, 43, 64), rgbdin(65, 53, 79), rgbdin(76, 62, 92), rgbdin(40, 32, 48), rgbdin(53, 35, 24), rgbdin(65, 43, 30), rgbdin(76, 50, 35), rgbdin(40, 26, 18), rgbdin(53, 57, 29), rgbdin(65, 70, 36), rgbdin(76, 82, 42), rgbdin(40, 43, 22), rgbdin(100, 42, 32), rgbdin(122, 51, 39), rgbdin(142, 60, 46), rgbdin(75, 31, 24), rgbdin(26, 15, 11), rgbdin(31, 18, 13), rgbdin(37, 22, 16), rgbdin(19, 11, 8)])




def distance(a,b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2 + (a[2]-b[2])**2

rgb2hex = lambda r,g,b: '#%02x%02x%02x' %(r,g,b)

def plot_points(ax, points, pcolors, tp):
    for i in range(len(points)):
        p = points[i]
        if i==tp:
            ax.scatter(p[0], p[1], p[2], c=np.array([rgb2hex(*(pcolors[i]))]), marker="x")
        else:
            ax.scatter(p[0], p[1], p[2], c=np.array([rgb2hex(*(pcolors[i]))]))

class DataOutputStream:
    def __init__(self, stream):
        self.stream = stream

    def write_boolean(self, bool):
        self.stream.write(struct.pack('?', bool))

    def write_byte(self, val):
        self.stream.write(struct.pack('b', val))

    def write_unsigned_byte(self, val):
        self.stream.write(struct.pack('B', val))

    def write_char(self, val):
        self.stream.write(struct.pack('>H', ord(val)))

    def write_double(self, val):
        self.stream.write(struct.pack('>d', val))

    def write_float(self, val):
        self.stream.write(struct.pack('>f', val))

    def write_short(self, val):
        self.stream.write(struct.pack('>h', val))

    def write_unsigned_short(self, val):
        self.stream.write(struct.pack('>H', val))

    def write_long(self, val):
        self.stream.write(struct.pack('>q', val))

    def write_utf(self, string):
        self.stream.write(struct.pack('>H', len(string)))
        self.stream.write(string)

    def write_int(self, val):
        self.stream.write(struct.pack('>i', val))

def collect_stuff():
    dist = 37*37
    totl = 0
    usdl = 0
    tott = 0
    usdt = 0
    totp = 0
    usdp = 0
    edges = []
    pyramids = []
    triangles = []
    forbidden_edges = set()
    for i in range(len(dinpoints)):
        p1 = dinpoints[i]
        b = i//4
        for j in range(i+1, len(dinpoints)):
            p2 = dinpoints[j]
            abd = distance(p1, p2)
            if abd<dist:
                ab = p2-p1
                for k in range(0, len(dinpoints)):
                    if i==k or j==k: continue;
                    col = dinpoints[k]
                    plr = np.dot(ab, col-p1)/(np.dot(ab, ab))
                    pl = np.clip(plr, 0.,1.)
                    pp = p1+pl*ab
                    dis = np.dot(col-pp, col-pp)
                    if 0 <= plr <= 1 and dis < 0.5:
                        forbidden_edges.add((i,j))
                        break
                    elif (i==b+2 and j == b+3 and k in[b,b+1]):
                        print("Not forbidding",i,"..",j," due to k as it's",dis,"away")
    lsa=1
    for i in range(len(dinpoints)):
        print(i)
        p1x = xyzpoints[i]
        p1 = dinpoints[i]
        for j in range(i+1, len(dinpoints)):
            totl += 1
            p2x = xyzpoints[j]
            p2 = dinpoints[j]
            ab = p2-p1
            abx = p2x-p1x
            dis12 = distance(p1, p2)
            if dis12<dist and (i,j) not in forbidden_edges:
                dsq12 = sqrt(dis12)
                usdl += 1
                edges.append(np.array([i,j]))
                for k in range(j+1, len(dinpoints)):
                    p3x = xyzpoints[k]
                    p3 = dinpoints[k]
                    ac = p3-p1
                    acx = p3x-p1x
                    dis13 = distance(p1, p3)
                    dis23 = distance(p2, p3)
                    if dis13<dist and dis23<dist and (i,k) not in forbidden_edges and (j,k) not in forbidden_edges:
                        dsq13 = sqrt(dis13)
                        dsq23 = sqrt(dis23)
                        # n = np.cross(ab,ac)
                        # mat = np.array([ab,ac,n]).T
                        # if np.linalg.det(mat) >= 0.2:
                        #     usdt += 1
                        #     triangles.append((np.array([i,j,k]), np.linalg.inv(mat), dsq12+dsq13+dsq23))
                        for l in range(k+1, len(dinpoints)):
                            totp += 1
                            p4x = xyzpoints[l]
                            p4 = dinpoints[l]
                            ad = p4-p1
                            adx = p4x-p1x
                            dis14 =  distance(p1, p4)
                            dis24 =  distance(p2, p4)
                            dis34 =  distance(p3, p4)
                            if dis14<dist and dis24<dist and dis34<dist \
                                and (i,l) not in forbidden_edges and (j,l) not in forbidden_edges and (k,l) not in forbidden_edges:
                                dsq14 = sqrt(dis14)
                                dsq24 = sqrt(dis24)
                                dsq34 = sqrt(dis34)
                                mat = np.array([abx,acx,adx]).T
                                mda = np.abs(np.linalg.det(mat))
                                if mda >= 0.000001:
                                    usdp += 1
                                    pyramids.append((np.array([i,j,k,l]), np.linalg.inv(mat), dsq12+dsq13+dsq23+dsq14+dsq24+dsq34))
            else:
                # print("Ignoring",i,"..",j,"because forbidden:",((i,j) in forbidden_edges),"dist:",dis12,"<",dist,"=",(dis12<dist))
                pass
    opf = open("out.data", "wb")
    dos = DataOutputStream(opf)
    dos.write_int(usdl)
    for ar in edges:
        dos.write_unsigned_byte(ar[0])
        dos.write_unsigned_byte(ar[1])
    dos.write_int(usdt)
    didit = False
    for td in triangles:
        ar = td[0]
        dos.write_unsigned_byte(ar[0])
        dos.write_unsigned_byte(ar[1])
        dos.write_unsigned_byte(ar[2])
        dos.write_unsigned_byte(255)
        dos.write_float(td[2])
        if not didit:
            print("First float",td[2])
            didit=True
        for i in range(3):
            for j in range(3):
                dos.write_float(td[1][i][j])
    dos.write_int(usdp)
    for td in pyramids:
        ar = td[0]
        dos.write_unsigned_byte(ar[0])
        dos.write_unsigned_byte(ar[1])
        dos.write_unsigned_byte(ar[2])
        dos.write_unsigned_byte(ar[3])
        dos.write_float(td[2])
        for i in range(3):
            for j in range(3):
                dos.write_float(td[1][i][j])
    print("Pyramids:",usdp)
    print("Triangles:",usdt)
    print("Lines:",usdl,"of",totl,"forbidden",len(forbidden_edges))
    return (edges, triangles, pyramids)

#
# def search(r,g,b,dat):
#     lines,triangles,pyramids = dat
#     palette = points
#     col = np.array([*rgbdin(r,g,b)])
#     indices = np.array([0,0,0,0])
#     mf = np.array([0,0,0,0])
#     cd = 9999999
#     result=()
#     for i in range(204):
#         tv = col-palette[i]
#         dis = np.dot(tv,tv)
#         if dis < cd :
#             print("Point p at point",palette[i],"dist",dis)
#             result=palette[i]
#             cd=dis
#             indices=np.array([i,i,i,i])
#             mf=np.array([0,0,0,1])
#     for i in range(len(lines)):
#         a = palette[lines[i][0].item()]
#         b = palette[lines[i][1].item()]
#         ab = b-a
#         pl = np.dot(ab, col-a)/(np.dot(ab, ab))
#         plr=pl
#         pl = np.clip(pl, 0., 1.)
#         pp = a+pl*ab
#         dis = np.dot(col-pp, col-pp)+0.01*np.linalg.norm(ab)
#         if (dis < cd):
#             print("Point p at line",pl,"in",lines[i],"dist",dis,"tc",pp,"a",a,"b",b,"ab",ab,"pl",pl,"pp",pp,"plr",plr)
#             result=lines[i]
#             cd=dis
#             indices = np.array([lines[i][0], lines[i][1], lines[i][1], lines[i][1]])
#             mf=np.array([pl,0,0,2])
#     for i in range(len(triangles)):
#         a = palette[triangles[i][0][0].item()]
#         b = palette[triangles[i][0][1].item()]
#         c = palette[triangles[i][0][2].item()]
#         ab = a-b
#         ac = a-c
#         dat =triangles[i][1] @  (col-a)
#         if dat[0] <= -0.001 or dat[1] <= -0.001 or dat[0]+dat[1] > 1.001: continue
#         tc = a+dat[0]*ab+dat[1]*ac
#         dis = np.dot(tc-col, tc-col)
#         if triangles[i][0][0]==0 and triangles[i][0][1] == 1:
#             print("Point p at ",dat,"in",triangles[i],"dist",dis,"tc",tc,"dat",dat)
#         if(dis < cd):
#             result=triangles[i]
#             cd=dis
#             indices = np.array([triangles[i][0][0], triangles[i][0][1], triangles[i][0][2], triangles[i][0][2]])
#             mf = np.array([dat[0], dat[1], 0,3])
#     cols = indices+np.array([4,4,4,4])
#     print("P itself",col)
#     return (cols, mf, cd, result, col)


def show():
    fig = plt.figure()
    ax = plt.axes(projection='3d')
    # ax.set_xlim(0,255)
    # ax.set_ylim(0,255)
    # ax.set_zlim(0,255)
    # ax.set_xlabel("Red")
    # ax.set_ylabel("Green")
    # ax.set_zlabel("Blue")
    ax.set_xlabel("L")
    ax.set_ylabel("a")
    ax.set_zlabel("b")
    ax.set_xlim(0,100)
    ax.set_ylim(-30, 30)
    ax.set_zlim(-30, 30)
    return fig

data = collect_stuff()
