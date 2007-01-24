// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                   OpenMS Mass Spectrometry Framework
// --------------------------------------------------------------------------
//  Copyright (C) 2003-2007 -- Oliver Kohlbacher, Knut Reinert
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Maintainer: Marc Sturm$
// --------------------------------------------------------------------------

#ifndef OPENMS_FORMAT_DTA2DFILE_H
#define OPENMS_FORMAT_DTA2DFILE_H

#include <OpenMS/KERNEL/DimensionDescription.h>
#include <OpenMS/DATASTRUCTURES/String.h>
#include <OpenMS/FORMAT/PeakFileOptions.h>

#include <fstream>
#include <iostream>

namespace OpenMS
{
  class String;

  /** 
	  @brief DTA2D File adapter.
	  
	  File adapter for files with three tab/space-separated columns.
	  
	  The default format is: retention time (seconds) , m/z , intensity.
		
	  If the first line starts with '#', a different order is defined by the 
	  the order of the keywords 'MIN' (retention time in minutes) or 'SEC' (retention time in seconds), 'MZ', and 'INT'.
	  
	  Example: '\#MZ MIN INT'
  	
  	The peaks of one retention time have to be in subsequent lines.
  	
  	@ingroup FileIO
  */
  class DTA2DFile
  {
    private:
      PeakFileOptions options_;

    public:

			/** @name Type definitions */
			//@{
			/// Dimension description
			typedef DimensionDescription < LCMS_Tag > DimensionDescription;
			/// Enum that defines MZ and RT dimension index
			enum DimensionId { MZ = DimensionDescription::MZ, RT = DimensionDescription::RT };
			//@}

      /** @name Constructors and Destructor */
      //@{
      /// Default constructor
      DTA2DFile();
      /// Destructor
      ~DTA2DFile();
      //@}
      
      /// Mutable access to the options for loading/storing 
      PeakFileOptions& getOptions();

      /// Non-mutable access to the options for loading/storing 
      const PeakFileOptions& getOptions() const;

      /**
      	@brief Loads a map from a DTA2D file.
      	
      	@p map has to be a MSExperiment or have the same interface.
      */
      template <typename MapType>
      void load(const String& filename, MapType& map) throw (Exception::FileNotFound, Exception::ParseError)
      {
	      //try to open file
				std::ifstream is(filename.c_str());
		    if (!is)
		    {
		      throw Exception::FileNotFound(__FILE__, __LINE__, __PRETTY_FUNCTION__, filename);
		    }
			
				map.reset();
			
				// temporary variables to store the data in
				std::vector<String> strings(3);
				typename MapType::SpectrumType spec;
				spec.setRetentionTime(-1.0);
				typename MapType::SpectrumType::PeakType p;
				typename MapType::SpectrumType::PeakType::CoordinateType rt(0.0);
				char delimiter;
			
				// default dimension of the data
				UnsignedInt rt_dim = 0;
				UnsignedInt mz_dim = 1;
				UnsignedInt int_dim = 2;
				
				//RT unit (default is seconds)
				bool time_in_minutes = false;
				
				// string to store the current line in
		    String line;
		
		    while (getline(is,line,'\n'))
		    {
		    	line.trim();
		
					if ( line.empty() ) continue;
		
					//test which delimiter is used in the line
					if (line.has('\t'))
					{
						delimiter = '\t';
					}
					else
					{
						delimiter = ' ';
					}
		
		    	//is header line
			    if (line.hasPrefix("#"))
			    {
			    	line = line.substr(1).trim();
			    	line.split(delimiter,strings);
		
						// flags to check if dimension is set correctly
			    	bool rt_set = false;
			    	bool mz_set = false;
			    	bool int_set = false;
		
			    	//assign new order
			    	for (UnsignedInt i = 0 ; i<3;++i)
			    	{
			    		if ( strings[i]=="RT" || strings[i]=="RETENTION_TIME" || strings[i]=="MASS-TO-CHARGE" || strings[i]=="IT" || strings[i]=="INTENSITY")
			    		{
			    			std::cerr << "Warning: This file contains the deprecated keyword '" << strings[i] << "'." << std::endl;
			    			std::cerr << "         Please use only the new keywords SEC/MIN, MZ, INT." << std::endl;
			    		}
			    		if ( ( strings[i]=="SEC" || strings[i]=="RT" || strings[i]=="RETENTION_TIME" ) && rt_set==false)
			    		{
			    			rt_dim = i;
			    			rt_set = true;
			    		}
			    		else if ( ( strings[i]=="MIN") && rt_set==false)
			    		{
			    			rt_dim = i;
			    			rt_set = true;
			    			time_in_minutes = true;
			    		}
			    		else if ( ( strings[i]=="MZ" || strings[i]=="MASS-TO-CHARGE" ) && mz_set==false)
			    		{
			    			mz_dim = i;
			    			mz_set = true;
			    		}
			    		else if ( ( strings[i]=="INT" || strings[i]=="IT" || strings[i]=="INTENSITY" ) && int_set==false )
			    		{
			    			int_dim = i;
			    			int_set = true;
			    		}
			    		else
			    		{
			    			throw Exception::ParseError(__FILE__, __LINE__, __PRETTY_FUNCTION__, "Misformatted header line!" ,filename);
			    		}
			    	}
			    	continue;
			    }
		
					try
					{
						line.split(delimiter,strings);
						if (strings.size()!=3)
						{
							throw Exception::ParseError(__FILE__, __LINE__, __PRETTY_FUNCTION__, std::string("Bad data line: \"")+line+"\"" ,filename);
						}
						//std::cout <<"'"<< strings[0] << "' '" << strings[1] << "' '" << strings[2] << "'"<< std::endl;
						//fill peak
						double mz = strings[mz_dim].toDouble();
						double intensity = strings[int_dim].toDouble();
						p.setIntensity(intensity);
						p.getPosition()[0] = mz;
						rt = (strings[rt_dim].toDouble()) * (time_in_minutes ? 60.0 : 1.0);
						
						if ((options_.hasMZRange() && !options_.getMZRange().encloses(DPosition<1>(mz)))
						 || (options_.hasRTRange() && !options_.getRTRange().encloses(DPosition<1>(rt)))
						 || (options_.hasIntensityRange() && !options_.getIntensityRange().encloses(DPosition<1>(intensity))))
						{
							continue; // if peak is out of specified range
						}
					}
					// conversion to double or something else could have gone wrong
					catch ( Exception::Base & e )
					{
						throw Exception::ParseError(__FILE__, __LINE__, __PRETTY_FUNCTION__, std::string("Bad data line: \"")+line+"\"" ,filename);
					}
		
					// Retention time changed -> new Spectrum
					//std::cout << "rt: " << rt << " spec: " <<  spec.getRetentionTime() << "test: "<< rt-spec.getRetentionTime()<< std::endl;
					if (rt != spec.getRetentionTime())
					{
						if (spec.getRetentionTime() >= 0) // if not initial Spectrum
						{
							map.push_back(spec);  
							//std::cout << "NEW SPEC"<< std::endl;
						}
						spec.getContainer().clear();
						spec.setRetentionTime(rt);
					}
					//insert peak into the spectrum
					spec.getContainer().push_back(p);
				}
				
				if (spec.getRetentionTime() >= 0) map.push_back(spec);  // add last Spectrum
				is.close();		
      }

      /**
      	@brief Stores a map in a DTA2D file.
      	
      	@p map has to be a MSExperiment or have the same interface.
      */
      template <typename MapType>
      void store(const String& filename, const MapType& map) const throw (Exception::UnableToCreateFile)
			{
				std::ofstream os(filename.c_str());
				if (!os)
				{
					throw Exception::UnableToCreateFile(__FILE__, __LINE__, __PRETTY_FUNCTION__, filename);
				}
								
				// Iterate over all peaks of each spectrum and
				// write one line for each peak of the spectrum.
				for (typename MapType::const_iterator spec=map.begin(); spec!=map.end(); ++spec)
				{
					for (typename MapType::SpectrumType::ConstIterator it = spec->begin(); it != spec->end(); ++it)
					{
						// Write rt, m/z and intensity.
						os 	<< spec->getRetentionTime() << " "<< it->getPosition()[0] << " "<< it->getIntensity() << std::endl;
					}
					
				}
				os.close();	
			}
  };

} // namespace OpenMS

#endif // OPENMS_FORMAT_DTA2DFILE_H

