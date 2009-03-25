/*
 * The information in this file is
 * Copyright(c) 2007 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "DateTime.h"
#include "DataElement.h"
#include "Units.h"

#include <set>
#include <string>
#include <vector>

class DataVariant;

/**
 *  Signature with identifying attributes
 *
 *  A signature is an object that essentially consists of a list of
 *  data sets, along with optional units for each data set.
 *
 *  This subclass of Subject will notify upon the following conditions:
 *  - The following methods are called: setData(), setUnits().
 *  - Everything else documented in DataElement.
 *
 *  @see    DataElement
 */
class Signature : public DataElement
{
public:
   /**
    *  Emitted with any<std::pair<string,DataVariant> > when an attribute is added, or changed.
    */
   SIGNAL_METHOD(Signature, DataChanged)
   /**
    *  Emitted with any<std::pair<string,const Units*> > when a units object is added, or changed.
    */
   SIGNAL_METHOD(Signature, UnitsChanged)

   /**
    *  Gets a data set from the signature.
    *
    *  This method returns a data set from the signature in the form of a
    *  DataVariant. 
    *
    *  @param   name
    *           The name of the data set, as provided when the data set was
    *           added to the Signature.
    *
    *  @return  A DataVariant containing the requested data set. If no data
    *           set exists in the signature with the specified name, it will 
    *           return an invalid DataVariant.
    *
    *  @see  DataVariant::isValid()
    */
   virtual const DataVariant &getData(std::string name) const = 0;

   /**
    *  Adds a data set to the signature.
    *
    *  This method adds a data set to the signature. A deep copy of the
    *  DataVariant will be performed. If a data set already exists in the
    *  Signature with the name specified, it will be replaced with the new
    *  value.
    *
    *  @param   name
    *           The name of the data set to be added to the signature.
    *
    *  @param   data
    *           The data set to be added to the Signature. For example:
    *
    * @code
    * bool populateSignature(Signature *pSig, 
    *                        const vector<double> &wavelengths,
    *                        const vector<double> &reflectances)
    * {
    *    if (pSig == NULL) return false;
    *    pSig->setData("wavelengths", DataVariant(wavelengths));
    *    pSig->setData("reflectances", DataVariant(reflectances));
    *    return true;
    * }
    * @endcode
    *
    *  @notify  This method will notify signalDataChanged with
    *           any<std::pair<string,DataVariant> > after the 
    *           data set is added to the Signature.
    */
   virtual void setData(std::string name, const DataVariant &data) = 0;

   /**
    *  Returns the units object associated with the data set of the specified 
    *  name. 
    *
    *  @param   name
    *           The name of the units object to get from the signature.
    *
    *  @return  A pointer to the units object with the specified name. NULL
    *           will be returned if no Units object exists with the specified
    *           name.
    */
   virtual const Units *getUnits(std::string name) const = 0;

   /**
    *  Sets the units object associated with the data set of the specified
    *  name.
    *
    *  @param   name
    *           The name to associated with the units object.
    *
    *  @param   pUnits
    *           A pointer to the units object. Cannot be NULL.
    *
    *  @notify  This method will notify signalUnitsChanged with
    *           any<std::pair<string,const Units*> > after the 
    *           units object is added to the Signature.
    */
   virtual void setUnits(std::string name, const Units *pUnits) = 0;

   /**
    *  Gets the names associated with data in this Signature.
    *
    *  @return set of names
    */
   virtual std::set<std::string> getDataNames() const = 0;

   /**
    *  Gets the names associated with units in this Signature.
    *
    *  @return set of names
    */
   virtual std::set<std::string> getUnitNames() const = 0;

protected:
   /**
    * This should be destroyed by calling ModelServices::destroyElement.
    */
   virtual ~Signature() {}
};

#endif   // SIGNATURE_H
