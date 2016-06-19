#include "HDF5Wrapper.h"
#include <complex>

int main(){

    int rows = 4;
    int cols = 20;
    int start = 0;

    HDF5Wrapper* wrapper;
    wrapper = new HDF5Wrapper;

    //cout << "Opening file: " << wrapper->openFileToRead("hammer.hdf5") << endl;
    cout << "Opening file: " << wrapper->openFileToWrite("hammerreal.hdf5") << endl;

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

    
    cout << "Create dataset: " << wrapper->createRealDataset("samples", rows, cols) << endl;
    cout << "Write samples: " << wrapper->writeRealSamples("samples", rows, cols, start, write_samples) << endl;

    cout << "Opening file: " << wrapper->openFileToRead("hammerreal.hdf5") << endl;

    HDF5Wrapper* wrapper2;
    wrapper2 = new HDF5Wrapper;

    cout << "Opening file: " << wrapper2->openFileToRead("hammerreal.hdf5") << endl;

    double *read_samples;
    read_samples = new double[rows*cols];

    cout << "Reading samples: " << wrapper2->readRealSamples("samples", rows, cols, start, read_samples) << endl;

    for (int i = 0 ; i < rows; i ++)
    {
        for ( int j = 0; j < cols; j++)
        {
            cout << read_samples[i*cols+j] << ", ";
        }
        cout << endl;
    }

    delete []read_samples;
    delete []write_samples;
    delete wrapper;
    delete wrapper2;

    return 0;
}

