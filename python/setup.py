#!/usr/bin/env python
'''
Python distutils setup for for NengoCPP example

Copyright 2018 Simon D. Levy

MIT License
'''

from distutils.core import setup

setup (name = 'nengo_pidcontrol',
    version = '0.1',
    install_requires = ['PIL'],
    description = '',
    py_modules = ['nengo_pidcontrol',],
    author='Simon D. Levy',
    author_email='simon.d.levy@gmail.com',
    license='MIT',
    platforms='Linux; Windows; OS X'
    )
