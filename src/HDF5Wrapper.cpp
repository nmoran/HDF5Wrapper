/*
 * Methods for wrapper for writing to HDF5 files.
 *
 */

#include "HDF5Wrapper.h"


int HDF5Wrapper::openFileToRead(const char *filename){
    if (!this->isOpenToRead && !this->isOpenToWrite)
        {
        try{
            this->file_ptr = new H5File(filename, H5F_ACC_RDONLY);
            this->isOpenToRead = true;
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "Already file open." << endl;
        return -1;
    }

}


int HDF5Wrapper::openFileToWrite(const char *filename){
    if (!this->isOpenToRead && !this->isOpenToWrite)
    {
        try{
            this->file_ptr = new H5File(filename, H5F_ACC_TRUNC);
            this->isOpenToWrite = true;
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "Already file open." << endl;
        return -1;
    }
}


int HDF5Wrapper::readComplexSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start_pos, complex<double> *samples){
    if ( this->isOpenToRead ) {
        try{
            DataSet dataset = this->file_ptr->openDataSet(datasetName);
            DataSpace dataspace = dataset.getSpace();
            hsize_t count[2];
            hsize_t start[2];
            hsize_t stride[2];
            hsize_t block[2];
            count[0] = rows; count[1] = cols;
            start[0] = start_pos; start[1] = 0;
            stride[0] = 1; stride[1] = 1;
            block[0] = 1; block[1] = 1;
            dataspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            // some debugging output
            /*hsize_t dims_out[2];
            int rank = dataspace.getSimpleExtentNdims();
            int ndims = dataspace.getSimpleExtentDims( dims_out, NULL);
            cout << "rank " << rank << ", dimensions " <<
                (unsigned long)(dims_out[0]) << " x " <<
                (unsigned long)(dims_out[1]) << endl;*/
            count[0] = rows*cols;
            start[0] = 0;
            stride[0] = 1;
            block[0] = 1;
            DataSpace mspace(1, count);
            mspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            dataset.read(samples, *this->complexType_ptr, mspace, dataspace);
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "A file must be open for reading." << endl;
        return -1;
    }
}

int HDF5Wrapper::createComplexDataset(const char *datasetName, unsigned long rows, unsigned long cols)
{
    if ( this->isOpenToWrite ) {
        try{
            /*
            * Create property list for a dataset and set up fill values.
            */
            complex<double> fillvalue = 0.0; /* Fill value for the dataset */
            DSetCreatPropList plist;
            plist.setFillValue(*this->complexType_ptr, &fillvalue);
            hsize_t fdim[2];
            fdim[0] = rows; fdim[1] = cols;
            DataSpace fspace(2, fdim);
            this->file_ptr->createDataSet(datasetName, *this->complexType_ptr, fspace, plist);
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "A file must be open for writing." << endl;
        return -1;
    }
}


int HDF5Wrapper::writeComplexSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start_pos, complex<double> *samples){
    if ( this->isOpenToWrite ) {
        try{
            DataSet dataset = this->file_ptr->openDataSet(datasetName);
            DataSpace dataspace = dataset.getSpace();
            hsize_t count[2];
            hsize_t start[2];
            hsize_t stride[2];
            hsize_t block[2];
            count[0] = rows; count[1] = cols;
            start[0] = start_pos; start[1] = 0;
            stride[0] = 1; stride[1] = 1;
            block[0] = 1; block[1] = 1;
            dataspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            count[0] = rows*cols;
            start[0] = 0;
            stride[0] = 1;
            block[0] = 1;
            DataSpace mspace(1, count);
            mspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            dataset.write(samples, *this->complexType_ptr, mspace, dataspace);
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "A file must be open for writing." << endl;
        return -1;
    }
}


int HDF5Wrapper::readRealSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start_pos, double *samples){
    if ( this->isOpenToRead ) {
        try{
            DataSet dataset = this->file_ptr->openDataSet(datasetName);
            DataSpace dataspace = dataset.getSpace();
            hsize_t count[2];
            hsize_t start[2];
            hsize_t stride[2];
            hsize_t block[2];
            count[0] = rows; count[1] = cols;
            start[0] = start_pos; start[1] = 0;
            stride[0] = 1; stride[1] = 1;
            block[0] = 1; block[1] = 1;
            dataspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);

            // some debugging output
            /*hsize_t dims_out[2];
            int rank = dataspace.getSimpleExtentNdims();
            int ndims = dataspace.getSimpleExtentDims( dims_out, NULL);
            cout << "rank " << rank << ", dimensions " <<
                (unsigned long)(dims_out[0]) << " x " <<
                (unsigned long)(dims_out[1]) << endl;*/
            count[0] = rows*cols;
            start[0] = 0;
            stride[0] = 1;
            block[0] = 1;
            DataSpace mspace(1, count);
            mspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            dataset.read(samples, PredType::NATIVE_DOUBLE, mspace, dataspace);
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "A file must be open for reading." << endl;
        return -1;
    }
}

int HDF5Wrapper::createRealDataset(const char *datasetName, unsigned long rows, unsigned long cols)
{
    if ( this->isOpenToWrite ) {
        try{
            /*
            * Create property list for a dataset and set up fill values.
            */
            double fillvalue = 0.0; /* Fill value for the dataset */
            DSetCreatPropList plist;
            plist.setFillValue(PredType::NATIVE_DOUBLE, &fillvalue);
            hsize_t fdim[2];
            fdim[0] = rows; fdim[1] = cols;
            DataSpace fspace(2, fdim);
            this->file_ptr->createDataSet(datasetName, PredType::NATIVE_DOUBLE, fspace, plist);
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "A file must be open for writing." << endl;
        return -1;
    }
}


int HDF5Wrapper::writeRealSamples(const char *datasetName, unsigned long rows, unsigned long cols, unsigned long start_pos, double *samples){
    if ( this->isOpenToWrite ) {
        try{
            DataSet dataset = this->file_ptr->openDataSet(datasetName);
            DataSpace dataspace = dataset.getSpace();
            hsize_t count[2];
            hsize_t start[2];
            hsize_t stride[2];
            hsize_t block[2];
            count[0] = rows; count[1] = cols;
            start[0] = start_pos; start[1] = 0;
            stride[0] = 1; stride[1] = 1;
            block[0] = 1; block[1] = 1;
            dataspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            count[0] = rows*cols;
            start[0] = 0;
            stride[0] = 1;
            block[0] = 1;
            DataSpace mspace(1, count);
            mspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            dataset.write(samples, PredType::NATIVE_DOUBLE, mspace, dataspace);
        } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "A file must be open for writing." << endl;
        return -1;
    }
}


int HDF5Wrapper::getDatasetDims(const char *datasetName, unsigned long &rows, unsigned long &cols){
    if ( this->isOpenToRead || this->isOpenToWrite ) {
        try{
            DataSet dataset = this->file_ptr->openDataSet(datasetName);
            DataSpace dataspace = dataset.getSpace();
            int rank = dataspace.getSimpleExtentNdims();
            hsize_t dims_out[rank];
            int ndims = dataspace.getSimpleExtentDims( dims_out, NULL);

            rows = (unsigned long)(dims_out[0]);
            cols = (unsigned long)(dims_out[1]);
         } catch (Exception error)  {
            error.printError();
            return -1;
        }
        return 0;
    } else {
        cout << "A file must be open which contains this dataset." << endl;
        return -1;
    }
}

void HDF5Wrapper::close(){
  // Flush buffers if not empty and in write mode.
  if (this->isOpenToWrite){
    for (std::list<HDF5Buffer*>::iterator it = this->buffers.begin(); it != this->buffers.end(); ++it){
      (*it)->flushBuffer();
    }
  }

  if (this->isOpenToRead || this->isOpenToWrite) {
    this->file_ptr->close();
    this->isOpenToRead = false;
    this->isOpenToWrite = false;
  }
}


HDF5Buffer* HDF5Wrapper::setupRealSamplesBuffer(const char *datasetName, unsigned long start_row, unsigned long bufferSizeRows){
  DataSet dataset = this->file_ptr->openDataSet(datasetName);
  unsigned long rows, cols;
  this->getDatasetDims(datasetName, rows, cols);
  HDF5Buffer *buffer = new HDF5Buffer(dataset, cols, start_row*cols, bufferSizeRows*cols, rows*cols);
  this->buffers.push_back(buffer);
  return buffer;
}


int HDF5Buffer::flushBuffer(){
  if (this->bufferLevel > 0){
    if((this->bufferLevel % this->bufferCols) != 0  ){
      cout << "Can only write buffers which contain an integer number of rows." << endl;
      return -1;
    }
    try{
      DataSpace dataspace = this->dataset.getSpace();
      hsize_t count[2];
      hsize_t start[2];
      hsize_t stride[2];
      hsize_t block[2];
      count[0] = this->bufferLevel/this->bufferCols; count[1] = this->bufferCols;
      start[0] = this->bufferStart/this->bufferCols; start[1] = 0;
      stride[0] = 1; stride[1] = 1;
      block[0] = 1; block[1] = 1;
      dataspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
      count[0] = this->bufferLevel;
      start[0] = 0;
      stride[0] = 1;
      block[0] = 1;
      DataSpace mspace(1, count);
      mspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
      this->dataset.write(this->samplesBuffer, PredType::NATIVE_DOUBLE, mspace, dataspace);
      this->bufferStart = this->bufferStart + this->bufferLevel;
      this->bufferLevel = 0;
    } catch (Exception error)  {
      error.printError();
      return -1;
    }
    return 0;
  } else {
    return 0;
  }
}


int HDF5Buffer::cycleBuffer(){
  if ((this->bufferStart + this->bufferLevel) < this->datasetSize){
    if((this->bufferLevel % this->bufferCols) != 0  ){
      cout << "Can only read buffers which contain an integer number of rows." << endl;
      return -1;
    }
    try{
      DataSpace dataspace = this->dataset.getSpace();
      hsize_t count[2];
      hsize_t start[2];
      hsize_t stride[2];
      hsize_t block[2];
      unsigned long readSize = this->bufferSize;
      if ((this->bufferStart + this->bufferLevel + this->bufferSize) > this->datasetSize){
        readSize = this->datasetSize - (this->bufferStart + this->bufferLevel);
      }
      count[0] = readSize/this->bufferCols; count[1] = this->bufferCols;
      start[0] = (this->bufferStart + this->bufferLevel)/this->bufferCols; start[1] = 0;
      stride[0] = 1; stride[1] = 1;
      block[0] = 1; block[1] = 1;
      dataspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
      count[0] = readSize;
      start[0] = 0;
      stride[0] = 1;
      block[0] = 1;
      DataSpace mspace(1, count);
      mspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
      this->dataset.read(this->samplesBuffer, PredType::NATIVE_DOUBLE, mspace, dataspace);
      this->bufferStart = this->bufferStart + this->bufferLevel;
      this->bufferFill = readSize;
      this->bufferLevel = 0;
    } catch (Exception error)  {
      error.printError();
      return -1;
    }
    return 0;
  } else {
    return 0;
  }
}


int HDF5Buffer::writeToBuffer(double *samples, unsigned long len){
  if ((this->bufferSize - this->bufferLevel) < len){
    this->flushBuffer();
  }
  memcpy(&this->samplesBuffer[this->bufferLevel], samples, len * sizeof(double));
  this->bufferLevel += len;
}


int HDF5Buffer::readFromBuffer(double *samples, unsigned long len){
  if ((this->bufferFill - this->bufferLevel) < len){
    this->cycleBuffer();
  }
  memcpy(samples, &this->samplesBuffer[this->bufferLevel], len * sizeof(double));
  this->bufferLevel += len;
}


