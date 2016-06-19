/*
 * Header file for wrapper for writing to HDF5 files.
 *
 */

#include "H5Cpp.h"
#include <iostream>
#include <complex>
#include <string.h>
#include <list>

#ifndef HDF5WRAPPER_H
#define HDF5WRAPPER_H



using namespace H5;
using namespace std;


class HDF5Buffer{

 private:
  double *samplesBuffer;
  unsigned long bufferSize, bufferLevel, datasetSize, bufferFill;
  hsize_t bufferCols, bufferStart;
  DataSet dataset;

 public:
  HDF5Buffer(DataSet dataset, unsigned long cols, unsigned long start_pos, unsigned long bufferSize, unsigned long datasetSize){
    this->dataset = dataset;
    this->bufferSize = bufferSize;
    this->samplesBuffer = new double[bufferSize];
    this->bufferLevel = 0;
    this->bufferCols = cols;
    this->bufferStart = start_pos;
    this->datasetSize = datasetSize;
    this->bufferFill = 0;
  }

  int flushBuffer(); // when using as a write buffer.
  int cycleBuffer(); // when using as a read buffer.
  int writeToBuffer(double *samples, unsigned long len);
  int readFromBuffer(double *samples, unsigned long len);
  ~HDF5Buffer(){
    delete []this->samplesBuffer;
  }

};


class HDF5Wrapper{
    private:
    H5File *file_ptr;
    bool isOpenToRead;
    bool isOpenToWrite;
    CompType *complexType_ptr;
    std::list<HDF5Buffer*> buffers;

    public:
    HDF5Wrapper(){
        // Initialise flags to false
        this->isOpenToRead = false;
        this->isOpenToWrite = false;

        // Setup complex type that is compatible with python API.
        const H5std_string STR_REAL("r");
        const H5std_string STR_IMAG("i");
        //this->complexType_ptr = new CompType(sizeof(complex<double>));
        this->complexType_ptr = new CompType(2*sizeof(double));
        //this->complexType_ptr->insertMember(STR_REAL, 0, PredType::NATIVE_DOUBLE);
        //this->complexType_ptr->insertMember(STR_IMAG, sizeof(double), PredType::NATIVE_DOUBLE);
    }

    ~HDF5Wrapper(){
        this->close();

        // clear allocated data structures.
        delete this->complexType_ptr;
        if (this->isOpenToRead || this->isOpenToWrite){
            delete this->file_ptr;
        }

        while(!this->buffers.empty()){
          HDF5Buffer *buffer = this->buffers.front();
          this->buffers.pop_front();
          delete buffer;
        }
    }

    int openFileToRead(const char *filename);
    int openFileToWrite(const char *filename);
    int readComplexSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start, complex<double> *samples);
    int createComplexDataset(const char *datasetName, unsigned long rows, unsigned long cols);
    int writeComplexSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start_pos, complex<double> *samples);
    int readRealSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start, double *samples);
    int createRealDataset(const char *datasetName, unsigned long rows, unsigned long cols);
    int writeRealSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start_pos, double *samples);
    HDF5Buffer* setupRealSamplesBuffer(const char *datasetName, unsigned long start_row, unsigned long bufferSizeRows=1000);
    int getDatasetDims(const char *datasetName, unsigned long &rows, unsigned long &cols);
    void close();
};




#endif
