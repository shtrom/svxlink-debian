/**
@file	 DtmfDecoder.h
@brief   This file contains the base class for implementing a DTMF decoder
@author  Tobias Blomberg / SM0SVX
@date	 2008-02-06

\verbatim
SvxLink - A Multi Purpose Voice Services System for Ham Radio Use
Copyright (C) 2004-2008  Tobias Blomberg / SM0SVX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/


#ifndef DTMF_DECODER_INCLUDED
#define DTMF_DECODER_INCLUDED


/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <sigc++/sigc++.h>
#include <string>


/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/

#include <AsyncAudioSink.h>
#include <AsyncConfig.h>


/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Forward declarations
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Namespace
 *
 ****************************************************************************/

//namespace MyNameSpace
//{

/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/

/*
 *----------------------------------------------------------------------------
 * Macro:   
 * Purpose: 
 * Input:   
 * Output:  
 * Author:  
 * Created: 
 * Remarks: 
 * Bugs:    
 *----------------------------------------------------------------------------
 */


/*
 *----------------------------------------------------------------------------
 * Type:    
 * Purpose: 
 * Members: 
 * Input:   
 * Output:  
 * Author:  
 * Created: 
 * Remarks: 
 *----------------------------------------------------------------------------
 */
    


/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Class definitions
 *
 ****************************************************************************/

/**
 * @brief   This is the base class for implementing a DTMF decoder
 * @author  Tobias Blomberg, SM0SVX
 * @date    2008-02-06
 */   
class DtmfDecoder : public sigc::trackable, public Async::AudioSink
{
  public:
    /**
     * @brief 	Create a new DTMF decoder object
     * @param 	cfg A previously initialised configuration object
     * @param 	name The name of the receiver configuration section
     * @returns Returns a new DTMF object or 0 on failure
     *
     * Use this function to create new DTMF decoder objects. What DTMF
     * decoder type to create is determined by the configuration pointed
     * out by the arguments to this function. The section pointed out should
     * contain a configuration variable DTMF_DEC_TYPE that points out the
     * decoder type to use. Valid values are: INTERNAL, S54S
     */
    static DtmfDecoder *create(Async::Config &cfg, const std::string& name);
    
    /**
     * @brief 	Destructor
     */
    virtual ~DtmfDecoder(void) {}
    
    /**
     * @brief 	Initialize the DTMF decoder
     * @returns Returns \em true if the initialization was successful or
     *          else \em false.
     *
     * Call this function to initialize the DTMF decoder. It must be called
     * before using it.
     */
    virtual bool initialize(void);
    
    /**
     * @brief 	Find out what the configured hangtime is
     * @returns Returns the configured hangtime in milliseconds
     */
    int hangtime(void) const { return m_hangtime; }
    
    /**
     * @brief 	Write samples into the DTMF decoder
     * @param 	samples The buffer containing the samples
     * @param 	count The number of samples in the buffer
     * @return	Returns the number of samples that has been taken care of
     */
    virtual int writeSamples(const float *samples, int count) { return count; }
    
    /**
     * @brief 	Tell the DTMF decoder to flush the previously written samples
     *
     * This function is used to tell the sink to flush previously written
     * samples. When done flushing, the sink should call the
     * sourceAllSamplesFlushed function.
     */
    virtual void flushSamples(void)
    {
      sourceAllSamplesFlushed();
    }
    
    /**
     * @brief 	Return the active digit
     * @return	Return the active digit if any or a '?' if none.
     */
    virtual char activeDigit(void) const = 0;

    /*
     * @brief 	A signal that is emitted when a DTMF digit is first detected
     * @param 	digit The detected digit
     */
    sigc::signal<void, char> digitActivated;

    /*
     * @brief 	A signal that is emitted when a DTMF digit is no longer present
     * @param 	digit 	  The detected digit
     * @param 	duration  The time that the digit was active
     */
    sigc::signal<void, char, int> digitDeactivated;
    
    
  protected:
    /**
     * @brief 	Constructor
     * @param 	cfg A previously initialised configuration object
     * @param 	name The name of the receiver configuration section
     *
     * DtmfDecoder objects are created by calling DtmfDecoder::create.
     */
    DtmfDecoder(Async::Config &cfg, const std::string &name)
      : m_cfg(cfg), m_name(name), m_hangtime(DEFAULT_HANGTIME) {}
    
    Async::Config &cfg(void) { return m_cfg; }
    const std::string &name(void) const { return m_name; }
    
    
  private:
    static const int DEFAULT_HANGTIME = 0;
    
    Async::Config   m_cfg;
    std::string     m_name;
    int       	    m_hangtime;
    
};  /* class DtmfDecoder */


//} /* namespace */

#endif /* DTMF_DECODER_INCLUDED */



/*
 * This file has not been truncated
 */
