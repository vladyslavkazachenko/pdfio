#include "istream_pool.h"

namespace pdfio
{
   
namespace pdf1_0
{
 
StreamPool::~StreamPool()
{
   
}

std::fstream &StreamPool::acquireStream()
{
   std::shared_ptr<std::fstream> istream;
   idleStreamsMutex_.lock();
   if(idleStreams_.empty())
   {
      idleStreamsMutex_.unlock();
      istream = std::make_shared<std::fstream>();
      busyStreamsMutex_.lock();
      busyStreams_.insert(istream);
      busyStreamsMutex_.unlock();
   }
   else
   {
      istream = *(idleStreams_.begin());
      idleStreams_.erase(idleStreams_.begin());
      idleStreamsMutex_.unlock();
      busyStreamsMutex_.lock();
      busyStreams_.insert(istream);
      busyStreamsMutex_.unlock();
   }
   return *istream;
}

void StreamPool::releaseStream(std::fstream &istream)
{
   std::shared_ptr<std::fstream> streamCopy;
   busyStreamsMutex_.lock();
   for(auto busyStream : busyStreams_)
   {
      if(busyStream.get() == &istream)
      {
         streamCopy = busyStream;
         busyStreams_.erase(busyStream);
         break;
      }
   }
   busyStreamsMutex_.unlock();
   idleStreamsMutex_.lock();
   idleStreams_.insert(streamCopy);
   idleStreamsMutex_.unlock();
}
  
}

}