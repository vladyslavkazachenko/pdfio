#include "read_destination.h"

#include "pdfio/log.h"
#include "read_indirect_reference.h"
#include "read_name.h"

namespace pdf1_0 = pdfio::pdf1_0;

#define LOG_PREFIX __PRETTY_FUNCTION__ << \
  ":istream[" << std::hex << std::showbase << \
  reinterpret_cast<unsigned long>(&istream) << "],destination[" << \
  reinterpret_cast<unsigned long>(&destination) << "]:"

std::istream &operator>>(std::istream &istream, 
   pdf1_0::Destination &destination)
{
   LOG_DEBUG(LOG_PREFIX << "enter\n");
   char ch;
   if(istream >> ch)
   {
      if(ch == '[')
      {
         pdf1_0::IndirectReference page;
         if(istream >> page)
         {
            pdf1_0::Name type;
            if(istream >> type)
            {
               if(type == "Fit")
               {
                  destination.fit().page_ = page;
                  if(istream >> ch)
                  {
                     if(ch != ']')
                     {
                        
                     }
                  }
               }
               else
               {
                  if(type == "FitH")
                  {
                     destination.fitH().page_ = page;
                     if(istream >> destination.fitH().top_)
                     {
                        if(ch != ']')
                        {
                           
                        }
                     }
                  }
                  else
                  {
                     if(type == "FitV")
                     {
                        destination.fitV().page_ = page;
                        if(istream >> destination.fitV().left_)
                        {
                           if(ch != ']')
                           {
                              
                           }
                        }
                     }
                     else
                     {
                        if(type == "FitR")
                        {
                           destination.fitR().page_ = page;
                           if(istream >> destination.fitR().left_)
                           {
                              if(istream >> destination.fitR().bottom_)
                              {
                                 if(istream >> destination.fitR().right_)
                                 {
                                    if(istream >> destination.fitR().top_)
                                    {
                                       if(ch != ']')
                                       {
                                 
                                       }
                                    }
                                 }
                              }
                           }
                        }
                        else
                        {
                           if(type == "XYZ")
                           {
                              destination.xyz().page_ = page;
                              if(istream >> destination.xyz().left_)
                              {
                                 if(istream >> destination.xyz().top_)
                                 {
                                    if(istream >> destination.xyz().zoom_)
                                    {
                                       if(ch != ']')
                                       {
                                 
                                       }
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }   
         }
      }
   }
   LOG_DEBUG(LOG_PREFIX << "leave\n");
   return istream;
}
