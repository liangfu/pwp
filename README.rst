=====================
 The CompVis Library
=====================

Introduction
============

The CompVis library is built to demostrate its efficient and 
accurate implementation on a few Computer Vision tasks, including face
detection, face recognition, generic object tracking etc.

The following modules are implemented in current version:

===============================  ========================================================================================
       module name               description
===============================  ========================================================================================
``image warping``                image resizing, rotating in an efficient way (with 3, 4 or 6 parameters)
``level sets``                   image segmentation with composed energy function
``optical flow``                 implements the inverse compositional algorithms
``AAM``                          active appearance model for facial image alignment
``LDA``                          fisher discriminant analysis (linear classifier)
``KFD``                          kernel fisher discriminant (nonlinear,guassian kernel)
``PWP``                          pixel-wise posterior, a level sets based tracking framework
``particle filter``              a probabilistic tracking framework
``cascade detector``             implements the classic viola-jones detection framework, with pre-trained feature sets
``sparse coding``                implements ``orthogonal matching pursuit (OMP)`` and ``basis pursuit (BP)`` algorithms
===============================  ========================================================================================

More code will be available online soon !

License
=======

The source code is released under `MIT license <https://github.com/liangfu/compvis/blob/master/LICENSE>`_ . There is no actural restrictions in (re)-distributing the code in any form.
