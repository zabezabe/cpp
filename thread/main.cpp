#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <string>
#include <unistd.h>

#define MAX_COUNT 4
int counter = 1;
std::queue<std::vector<int>> LogQueue;
void SetQueue()
{
  while (counter != MAX_COUNT)
  {
    std::vector<int> datas;
    for (int i = 1; i <= counter; i++)
    {
      datas.push_back(i);
    }
    LogQueue.push(datas);
    counter++;
    sleep(2);
  }
}

void ThreadFunc(std::queue<std::vector<int>> *LogQueue_, int *counter_)
{
  std::queue<std::vector<int>> *ThreadQueue = LogQueue_;
  while (1)
  {
    if (ThreadQueue->empty())
    {
      std::cout << "Queue is empty!" << std::endl;
      sleep(1);
    }
    else
    {
      std::vector<int> x;
      std::string message;
      x = ThreadQueue->front();
      for (auto i : x)
      {
        message += std::to_string(i);
      }
      std::cout << message << std::endl;
      ThreadQueue->pop();
      if (*counter_ == MAX_COUNT)
      {
        std::cout << "Hello World!!" << std::endl;
        break;
      }
    }
  }
}

int main()
{
  // スレッド作成
  std::thread Thread(ThreadFunc, &LogQueue, &counter);
  // Queueへのセット
  SetQueue();
  Thread.join();
  return 0;
}