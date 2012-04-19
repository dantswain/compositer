# Compositer

Dan Swain, dan.t.swain@gmail.com, 4/18/2012

A simple video frame compositer.  Takes a video file with a fixed background and creates a composite image from a fix set of images.  Produces a multiple exposure-type effect.

Not very user friendly at present, but could be made to be pretty flexible.  Compiles on OS X if you have OpenCV installed using macports or similar, as long as `pkg-config opencv --cflags` works.  Managing the build using rake right now, so just run `rake` to compile.

Example image:

![Example](https://github.com/dantswain/compositer/raw/master/sample.jpg)

