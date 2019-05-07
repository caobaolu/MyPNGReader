/*=========================================================================

  Program:   Visualization Toolkit
  Module:    LXPNGReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   LXPNGReader
 * @brief   read PNG files
 *
 * LXPNGReader is a source object that reads PNG files.
 * It should be able to read most any PNG file
 *
 * @sa
 * vtkPNGWriter
*/

#ifndef LXPNGReader_h
#define LXPNGReader_h

#include "LXPNGModule.h" // For export macro
#include "vtkImageReader2.h"

class LXPNG_EXPORT LXPNGReader : public vtkImageReader2
{
public:
  static LXPNGReader *New();
  vtkTypeMacro(LXPNGReader,vtkImageReader2);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Is the given file a PNG file?
   */
  int CanReadFile(const char* fname) override;

  /**
   * Get the file extensions for this format.
   * Returns a string with a space separated list of extensions in
   * the format .extension
   */
  const char* GetFileExtensions() override
  {
      return ".png";
  }

  /**
   * Return a descriptive name for the file format that might be useful in a GUI.
   */
  const char* GetDescriptiveName() override
  {
      return "PNG";
  }

  /**
   * Given a 'key' for the text chunks, fills in 'beginEndIndex'
   * with the begin and end indexes. Values are stored between
   * [begin, end) indexes.
   */
  void GetTextChunks(const char* key, int beginEndIndex[2]);
  /**
   * Returns the text key stored at 'index'.
   */
  const char* GetTextKey(int index);
  /**
   * Returns the text value stored at 'index'. A range of indexes
   * that store values for a certain key can be obtained by calling
   * GetTextChunks.
   */
  const char* GetTextValue(int index);
  /**
   * Return the number of text chunks in the PNG file.
   * Note that we don't process compressed or international text entries
   */
  size_t GetNumberOfTextChunks();

  //@{
  /**
   * Set/Get if data spacing should be calculated from the PNG file.
   * Use default spacing if the PNG file don't have valid pixel per meter parameters.
   * Default is false.
   */
  vtkSetMacro(ReadSpacingFromFile, bool);
  vtkGetMacro(ReadSpacingFromFile, bool);
  vtkBooleanMacro(ReadSpacingFromFile, bool);
  //@}
protected:
  LXPNGReader();
  ~LXPNGReader() override;

  void ExecuteInformation() override;
  void ExecuteDataWithInformation(vtkDataObject *out, vtkInformation *outInfo) override;
  template <class OT>
    void LXPNGReaderUpdate(vtkImageData *data, OT *outPtr);
  template <class OT>
    void LXPNGReaderUpdate2(
      OT *outPtr, int *outExt, vtkIdType *outInc, long pixSize);


private:
  LXPNGReader(const LXPNGReader&) = delete;
  void operator=(const LXPNGReader&) = delete;

  class vtkInternals;
  vtkInternals* Internals;
  bool ReadSpacingFromFile;
};
#endif
