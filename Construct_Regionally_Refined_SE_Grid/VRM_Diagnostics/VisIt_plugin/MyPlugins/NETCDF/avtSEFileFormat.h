/*****************************************************************************
*
* Copyright (c) 2000 - 2015, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#ifndef AVT_SE_FILE_FORMAT_H
#define AVT_SE_FILE_FORMAT_H
#include <avtSTSDFileFormat.h>
#include <avtMTSDFileFormat.h>
#include <vectortypes.h>
#include <map>

class NETCDFFileObject;
class avtFileFormatInterface;
class avtSEReader;

// ****************************************************************************
//  Class: avtSE_MTSD_NETCDFFileFormat
//
//  Purpose:
//      Reads in SE files with time dimension as a plugin to VisIt.
//
//  Programmer: Patrick Callaghan
//  Creation:   Sept 22 2016
//
//  Modifications:
//
// ****************************************************************************

class avtSE_MTSD_FileFormat : public avtMTSDFileFormat
{
public:
   static bool         Identify(NETCDFFileObject *);
   static avtFileFormatInterface *CreateInterface(NETCDFFileObject *f, 
                       const char *const *list, int nList, int nBlock);

                       avtSE_MTSD_FileFormat(const char *);
                       avtSE_MTSD_FileFormat(const char *, NETCDFFileObject *);
    virtual           ~avtSE_MTSD_FileFormat();

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    virtual void           GetCycles(std::vector<int> &);
    virtual void           GetTimes(std::vector<double> &);

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "SE MT NETCDF"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);

    virtual void          *GetAuxiliaryData(const char  *var,
                                            int    timeState,
                                            const char *type,
                                            void       *args,
                                            DestructorFunction &);

protected:
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);

    avtSEReader *reader;
};

// ****************************************************************************
//  Class: avtSE_STSD_FileFormat
//
//  Purpose:
//      Reads in SE files as a plugin to VisIt.
//
//  Programmer: Patrick Callaghan
//  Creation:   Sept 22 2016
//
//  Modifications:
//
// ****************************************************************************

class avtSE_STSD_FileFormat : public avtSTSDFileFormat
{
public: 
   static bool         Identify(NETCDFFileObject *);
   static avtFileFormatInterface *CreateInterface(NETCDFFileObject *f, 
                       const char *const *list, int nList, int nBlock);

                       avtSE_STSD_FileFormat(const char *filename, 
                                                NETCDFFileObject *);
                       avtSE_STSD_FileFormat(const char *filename);
    virtual           ~avtSE_STSD_FileFormat();

    virtual int            GetCycle();
    virtual double         GetTime();

    virtual const char    *GetType(void) { return "SE ST NETCDF"; }
    virtual void           ActivateTimestep(void); 
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(const char *);
    virtual vtkDataArray  *GetVar(const char *);
    virtual vtkDataArray  *GetVectorVar(const char *);

    virtual void          *GetAuxiliaryData(const char *var,
                                            const char *type,
                                            void *args,
                                            DestructorFunction &);


protected:
    virtual int            GetCycleFromFilename(const char *f) const;
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *);
private:
    avtSEReader *reader;
};

#endif
