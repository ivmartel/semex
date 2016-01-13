/**
* \file NewImageIOFactory.cpp
* \brief Implementation of the thelib::NewImageIOFactory class.
*/
#include "NewImageIOFactory.h"

// ITK
#include <itkCreateObjectFunction.h>
#include <itkVersion.h>
// local
#include "NewImageIO.h"

namespace thelib
{

NewImageIOFactory::NewImageIOFactory()
{
    this->RegisterOverride("itkImageIOBase",
                         "NewImageIO",
                         "New Image IO",
                         1,
                         itk::CreateObjectFunction<NewImageIO>::New());
}
  
NewImageIOFactory::~NewImageIOFactory()
{
}

const char* 
NewImageIOFactory::GetITKSourceVersion(void) const
{
    return ITK_SOURCE_VERSION;
}

const char* 
NewImageIOFactory::GetDescription(void) const
{
    return "New ImageIO Factory, allows the loading of 'New' images into insight.";
}

} // end namespace thelib
