#pragma once

#include <fstream>
#include <set>
#include <memory>
#include <mutex>

namespace pdfio
{
   
namespace pdf1_0
{
   
class StreamPool
{
public:
   StreamPool() = default;
   StreamPool(const StreamPool &) = delete;
   StreamPool &operator=(const StreamPool &) = delete;
   ~StreamPool();
   
   std::fstream &acquireStream();
   void releaseStream(std::fstream &);
   
private:
   std::set<std::shared_ptr<std::fstream>> idleStreams_;
   std::set<std::shared_ptr<std::fstream>> busyStreams_;
   std::mutex idleStreamsMutex_;
   std::mutex busyStreamsMutex_;
};
   
}
   
}