ADD_LIBRARY(HDF5Wrapper SHARED HDF5Wrapper.cpp)
TARGET_LINK_LIBRARIES(HDF5Wrapper ${HDF5_C_LIBRARIES} ${HDF5_CXX_LIBRARIES})
INSTALL(TARGETS HDF5Wrapper DESTINATION lib)
INSTALL(FILES HDF5Wrapper.h DESTINATION include)
