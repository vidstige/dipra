# DIPRA
DIPRA, the DIffrentiable Polygon RAsterizer. High precision, antialised polygon rendering. Suitable for computational optimization and the like. It's not very fast, but produces perfefct subpixel rasters. For displaying polygons, usually some subsampling of a faster rasterizer can be used. But when used e.g. in optimization processes and similar, pixel-perfect rendering may be vital, and that's where DIPRA fits in.

![Example render (`convert images/0.pgm -interpolate nearest -filter point -resize 1600% images/0.png`)](images/0.png)

## Building

To build the DIPRA static library, just issue
    
    make

To also build the example program run

    make examples


## Python bindings

To test the Python bindings, first create a virtual environment for your python version of choice, and activate it

    python3.10 -m venv venv/
    source venv/bin/activate

Then install it (together with the test dependencies) and run the test suite

    pip install bindings/python/[test]
    pytest bindings/python/


## Author
Samuel Carlsson