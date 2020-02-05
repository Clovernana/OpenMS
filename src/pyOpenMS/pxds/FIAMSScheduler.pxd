from Types cimport *
from libcpp.map cimport map as libcpp_map
from libcpp.vector cimport vector as libcpp_vector
from CsvFile cimport *

cdef extern from "</home/svegal/OpenMS/src/openms/include/OpenMS/ANALYSIS/ID/FIAMSScheduler.h>" namespace "OpenMS":

    cdef cppclass FIAMSScheduler "OpenMS::FIAMSScheduler":
        #
        # wrap-doc:
        #     ADD PYTHON DOCUMENTATION HERE
        #
        FIAMSScheduler() nogil except +
        FIAMSScheduler(FIAMSScheduler) nogil except +
        FIAMSScheduler(String filename, String base_dir) nogil except +
        void run() nogil except +
        libcpp_vector[ libcpp_map[ String, String ] ] getSamples() nogil except +
        String getBaseDir() nogil except +

