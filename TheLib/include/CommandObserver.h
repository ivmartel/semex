/**
* \file CommandObserver.h
* \brief Definition of the thelib::CommandObserver class.
*/
#ifndef THELIB_COMMANDOBSERVER_H
#define THELIB_COMMANDOBSERVER_H

// ITK
#include <itkCommand.h>

// namespace
namespace thelib
{

/**
* Observer class.
* Derives from itk::Command and reimplements
* the Execute() method.
* \ingroup TheLib
*/
class CommandObserver : public itk::Command 
{

public:

    //! Standard class typedefs.
    typedef CommandObserver Self;
    typedef itk::Command Superclass;
    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::ProcessObject ProcessType;
    
    typedef const ProcessType* ProcessPointer;
    
    //! Method for creation through the object factory.
    itkNewMacro( Self );

    //! Execute with non const input.
    void Execute(itk::Object *caller, const itk::EventObject & event)
    {
        Execute( (const itk::Object *)caller, event);
    }

    //! Execute with const input.
    void Execute(const itk::Object * object, const itk::EventObject & event)
    {
        ProcessPointer filter = dynamic_cast< ProcessPointer >( object );
        if( typeid( event ) == typeid( itk::ProgressEvent ) )
        {
            std::cout << "Progress = " << filter->GetProgress() << std::endl;
        }
        else if( typeid( event ) == typeid( itk::StartEvent ) )
        {
            std::cout << "Filter Starting ..." << std::endl;
            std::cout << std::endl;
        }
        else if( typeid( event ) == typeid( itk::EndEvent ) )
        {
            std::cout << std::endl;
            std::cout << "Filter Done !" << std::endl;
        }
    }

protected:

    //! Constructor: protect from instantiation.
    CommandObserver() {}

    //! Destructor: protect from instantiation.
    ~CommandObserver() {}
    
private:

    //! Copy constructor: purposely not implemented.
    CommandObserver( const Self& );

    //! Assignement operator: purposely not implemented.
    void operator=( const Self& );

}; // class CommandObserver

} // namespace thelib

#endif // THELIB_COMMANDOBSERVER_H
