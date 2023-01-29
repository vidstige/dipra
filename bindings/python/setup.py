from pathlib import Path
from setuptools import setup, Extension

#long_description = Path("README.md").read_text()
long_description = ''

setup(
    name='dipra',
    version='0.1',
    description='High precision polygon rasterizer',
    package_data={'dipra': ['__init__.pyi', 'py.typed']},
    ext_modules=[
        Extension(
            'dipra', [
                'dipramodule.c',
                '../../src/dipra.c', '../../src/bbox.c', '../../src/polygon.c'],
            depends=[
                'include/dipra/dipra.h', 'include/dipra/bbox.h', 'include/dipra/polygon.h',
                ],
            include_dirs=['../../include'],
        )
    ],
    long_description=long_description,
    author='Samuel Carlsson',
    author_email='samuel.carlsson@gmail.com',
    url='https://github.com/vidstige/dipra',
    license='BSD',
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Programming Language :: Python',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
    ],
    keywords='polygon, rasterizer, render, draw',
    extras_require={
        'test': ['pytest', 'numpy', 'pillow'],
    },
)