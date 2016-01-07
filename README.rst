Raft network simulator, used for testing/abusing `Raft <https://github.com/willemt/raft>`_.

Building
========

.. code-block:: bash
   :class: ignore

   make

Usage
=====

A network of 3 nodes with a message drop rate of 50%, message duplication rate of 20%, with a random seed initialized at 2:

.. code-block:: bash
   :class: ignore

   build/virtraft --nodes 3 --drop_rate 50 --dupe_rate 20 --seed 2
