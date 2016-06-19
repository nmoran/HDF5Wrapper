#include "../src/HDF5Wrapper.h"
#include <complex>

int main(){

    unsigned long rows = 4;
    unsigned long cols = 20;
    unsigned long start = 0;

    HDF5Wrapper *wrapper, *buffered_wrapper;
    wrapper = new HDF5Wrapper;
    buffered_wrapper = new HDF5Wrapper;

    //cout << "Opening file: " << wrapper->openFileToRead("hammer.hdf5") << endl;
    cout << "Opening file: " << wrapper->openFileToWrite("hammerreal.hdf5") << endl;
    cout << "Opening file: " << buffered_wrapper->openFileToWrite("hammerrealbuf.hdf5") << endl;

    double *write_samples;
    write_samples = new double[rows*cols];

    //set some values
    for (int i = 0 ; i < rows; i ++)
    {
        for ( int j = 0; j < cols; j++)
        {
            write_samples[i*cols+j] = 1.0/(double)(i*cols + j);
        }
    }

    cout << "Size of hsize_t structure: " << sizeof(hsize_t) << endl;
    cout << "Size of long long structure: " << sizeof(long) << endl;

    cout << "Create dataset: " << wrapper->createRealDataset("samples", rows, cols) << endl;
    cout << "Create dataset: " << buffered_wrapper->createRealDataset("samples", rows, cols) << endl;
    HDF5Buffer *buffer = buffered_wrapper->setupRealSamplesBuffer("samples", start, 1000000);
    cout << "Write samples: " << wrapper->writeRealSamples("samples", rows, cols, start, write_samples) << endl;
    cout << "Write samples buffered: " << buffer->writeToBuffer(write_samples, (rows/2)*cols) << endl;
    cout << "Write samples buffered: " << buffer->writeToBuffer(&write_samples[2*cols], (rows/2)*cols) << endl;
    wrapper->close();
    buffered_wrapper->close();


    HDF5Wrapper* wrapper2;
    wrapper2 = new HDF5Wrapper;

    cout << "Opening file: " << wrapper2->openFileToRead("hammerreal.hdf5") << endl;
    cout << "Opening file: " << buffered_wrapper->openFileToRead("hammerrealbuf.hdf5") << endl;

    double *read_samples, *read_samples2;
    read_samples = new double[rows*cols];
    read_samples2 = new double[rows*cols];

    cout << "Reading samples: " << wrapper2->readRealSamples("samples", rows, cols, start, read_samples) << endl;

    for (int i = 0 ; i < rows; i ++)
    {
        for ( int j = 0; j < cols; j++)
        {
            cout << read_samples[i*cols+j] << ", ";
        }
        cout << endl;
    }

    cout << "Reading samples2: " << buffered_wrapper->readRealSamples("samples", rows, cols, start, read_samples2) << endl;

    for (int i = 0 ; i < rows; i ++)
      {
        for ( int j = 0; j < cols; j++)
          {
            cout << read_samples2[i*cols+j] << ", ";
          }
        cout << endl;
      }


    delete []read_samples;
    delete []read_samples2;
    delete []write_samples;
    delete wrapper;
    delete buffered_wrapper;
    delete wrapper2;

    return 0;
}
