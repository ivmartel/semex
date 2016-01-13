/**
* \file NewImageIO.cpp
* \brief Implementation of the thelib::NewImageIO class.
*/
#include "NewImageIO.h"

// std
#include <fstream>
// ITK
#include <itksys/SystemTools.hxx>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

namespace thelib
{

NewImageIO::NewImageIO()
{
    // defaults
    m_Extension = ".new";
    m_FormatName = "new";
    m_FormatVersion = "1.0";
    
    this->SetNumberOfDimensions(3);
    m_PixelType = itk::ImageIOBase::SCALAR;
    m_ComponentType = itk::ImageIOBase::UCHAR;
    m_UseCompression = false;
    
    // spacing
    m_Spacing[0] = 1.0;
    m_Spacing[1] = 1.0;
    m_Spacing[2] = 1.0;

    // origin
    m_Origin[0] = 0.0;
    m_Origin[1] = 0.0;
    m_Origin[2] = 0.0;
    
    // write extensions
    this->AddSupportedWriteExtension( m_Extension.c_str() );
    // read extensions
    this->AddSupportedReadExtension( m_Extension.c_str() );
}

NewImageIO::~NewImageIO()
{
}

void NewImageIO::PrintSelf(std::ostream& os, itk::Indent indent) const
{
    Superclass::PrintSelf(os, indent);
    os << indent << "Extension: " << m_Extension << std::endl;
    os << indent << "FormatName: " << m_FormatName << std::endl;
    os << indent << "FormatVersion: " << m_FormatVersion << std::endl;
}
 
std::string NewImageIO::GetExtension( const std::string& filename ) const
{
    return itksys::SystemTools::GetFilenameLastExtension(filename);
}

std::string NewImageIO::GetRootName( const std::string& filename ) const
{
    const std::string fileExt = GetExtension(filename);
    // Create a base filename: i.e Image.ext --> Image
    if( fileExt.length() > 0  
        && filename.length() > fileExt.length() )
    {
        const std::string::size_type it = filename.find_last_of( fileExt );
        const std::string baseName( filename, 0, it-(fileExt.length()-1) );
        return baseName;
    }
    // Default to return same as input when the extension is nothing
    return filename;
}

std::string NewImageIO::GetHeaderFileName( const std::string& filename ) const
{
    std::string headerFilename = GetRootName(filename);
    headerFilename += ".new";
    return headerFilename;
}

std::string NewImageIO::GetImageFileName( const std::string& filename ) const
{
    std::string imageFilename = GetRootName(filename);
    imageFilename += ".raw";
    return imageFilename;
}

bool NewImageIO::CanReadFile(const char* file) 
{ 
    // First check the extension
    const std::string filename = file;
    if( filename == "" )
    {
        itkDebugMacro(<<"No filename specified.");
        return false;
    }

    // Now check the file header
    std::ifstream ifs( GetHeaderFileName(filename).c_str() );
    if( ifs.fail() )
    {
        return false;
    }
    std::string line;
    std::getline( ifs, line );
    line.erase(line.find_last_not_of(" \n\r\t")+1);
    const bool is_new = line.substr(line.size()-3, line.size()) == "new" ? true : false;
    if( !is_new )
    {
        return false;
    }
    ifs.close();

    return true;
}
  
void NewImageIO::ReadImageInformation()
{
    std::string begin;

    // open header file
    std::ifstream ifs( GetHeaderFileName(this->GetFileName()).c_str() );
    if( ifs.fail() )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Cannot open file.", ITK_LOCATION);
    }
    
    // format name
    ifs >> begin >> m_FormatName;
    if( begin != "formatName:" )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Bad line begin.", ITK_LOCATION);
    }
    
    // format version
    ifs >> begin >> m_FormatVersion;
    if( begin != "formatVersion:" )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Bad line begin.", ITK_LOCATION);
    }
    
    // dim
    ifs >> begin >> m_Dimensions[0] >> m_Dimensions[1] >> m_Dimensions[2];
    if( begin != "dims:" )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Bad line begin.", ITK_LOCATION);
    }
    
    // spacing
    ifs >> begin >> m_Spacing[0] >> m_Spacing[1] >> m_Spacing[2];
    if( begin != "spacing:" )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Bad line begin.", ITK_LOCATION);
    }
     
    // origin
    ifs >> begin >> m_Origin[0] >> m_Origin[1] >> m_Origin[2];
    if( begin != "origin:" )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Bad line begin.", ITK_LOCATION);
    }
    
    // close
    ifs.close();
}

void NewImageIO::Read(void* buffer)
{
    // open image file
    std::ifstream ifs( GetImageFileName(this->GetFileName()).c_str(), std::ios::binary );
    if( ifs.fail() )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Cannot open file.", ITK_LOCATION);
    }
    
    if( !this->ReadBufferAsBinary( ifs, buffer, this->GetImageSizeInBytes() ) )
    {
        throw itk::ImageFileReaderException(__FILE__, __LINE__, "Error while reading.", ITK_LOCATION);
    }
    
    // close
    ifs.close();
}


bool NewImageIO::CanWriteFile( const char* name )
{
    return true;
}

void NewImageIO::WriteImageInformation()
{
    // open header file
    std::ofstream ofs( GetHeaderFileName(this->GetFileName()).c_str() );
    if( ofs.fail() )
    {
        throw itk::ImageFileWriterException(__FILE__, __LINE__, "No input file.", ITK_LOCATION);
    }
    
    // format name
    ofs << "format name: " << m_FormatName << std::endl;
    // format version
    ofs << "format version: " << m_FormatVersion << std::endl;
    // dim
    ofs << "dim: " << m_Dimensions[0] << " " << m_Dimensions[1] << " " << m_Dimensions[2] << std::endl;
    // size
    ofs << "spacing: " << m_Spacing[0] << " " << m_Spacing[1] << " " << m_Spacing[2] << std::endl;
    // origin
    ofs << "origin: " << m_Origin[0] << " " << m_Origin[1] << " " << m_Origin[2] << std::endl;
    
    // close
    ofs.close();
}

void NewImageIO::Write(const void* buffer)
{
    // write the header
    this->WriteImageInformation();
    
    // open image file
    std::ofstream ofs( GetImageFileName(this->GetFileName()).c_str(), std::ios::binary | std::ios::app );
    if( ofs.fail() )
    {
        throw itk::ImageFileWriterException(__FILE__, __LINE__, "Cannot open file.", ITK_LOCATION);
    }
    
    const unsigned long numberOfBytes = this->GetImageSizeInBytes();

    char* tempBuffer = new char[ numberOfBytes ];
    memcpy( tempBuffer, buffer, numberOfBytes );
    ofs.write( tempBuffer, numberOfBytes );
    delete [] tempBuffer;    
    
    // close
    ofs.close();
}

} // end namespace thelib
