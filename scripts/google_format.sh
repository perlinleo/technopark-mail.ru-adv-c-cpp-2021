#!/bin/bash
pwd
clang-format -i -style=Google ../tf_idf_lib/include/*.h ../tf_idf_lib/source/*.c ../tf_idf_lib/source_threads/*.c