#ifndef __PROGTEST_AG1_1__
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <sstream>

namespace khomcvla_ag1_1
{
class CGraphTester;
//==================================================================================
class CGraph
{
private:
    enum class EQueue
    {
        EQUEUE_LEFT = 0,
        EQUEUE_RIGHT = 1
    };

    class CVertex
    {
    public:
        enum EState
        {
            ESTATE_WHITE = 1,
            ESTATE_GRAY = 2,
            ESTATE_BLACK = 3,
        };

        CVertex();

        void setPosition(int position) { m_position = position; }
        int getPosition() const { return m_position; }

        void setDistantion(int distantion) { m_distantion = distantion; }
        int getDistantion() const { return m_distantion; }

        void setSuitable(bool isSuitable) { m_isSuitable = isSuitable; }
        bool getSuitable() const { return m_isSuitable; }

        void setState(EState state) { m_state = state; }
        EState getState() const { return m_state; }

        std::vector<CVertex *> &getNeighbours() { return m_neighbours; }
        void addNeighbour(CVertex *neighbour);

        friend CGraphTester;

    private:
        int m_position;
        int m_distantion;
        bool m_isSuitable;
        EState m_state;
        std::vector<CVertex *> m_neighbours;
    };

public:
    CGraph(const int N, const int K);

    void fillGraph();
    void fillGraph(std::string leftQueue, std::string rightQueue);
    void constructNeighbours();
    void BFS(CVertex *vertex);
    int findSolution(std::string leftQueue, std::string rightQueue);

    std::vector<CVertex> &getQueue(EQueue queue);
    CVertex *getNeighbourReference(EQueue queue, int position);

private:
    const int m_N;
    const int m_K;
    int cleanerPosition;
    std::vector<CVertex> m_leftQueue;
    std::vector<CVertex> m_rightQueue;
};
//==================================================================================
CGraph::CGraph(const int N, const int K) : m_N(N),
                                           m_K(K)
{
    m_leftQueue.resize(m_N + 1);
    m_rightQueue.resize(m_N + 1);
    cleanerPosition = 0;
}
//==================================================================================
CGraph::CVertex::CVertex()
{
    m_distantion = -1;
    m_state = EState::ESTATE_WHITE;
    m_isSuitable = true;
}
//==================================================================================
void CGraph::CVertex::addNeighbour(CVertex *neighbour)
{
    if (this->getSuitable() && neighbour && neighbour->getSuitable())
    {
        m_neighbours.push_back(neighbour);
    }
}
//==================================================================================
CGraph::CVertex *CGraph::getNeighbourReference(EQueue queue, int position)
{
    std::vector<CGraph::CVertex> &q = queue == EQueue::EQUEUE_LEFT ? m_leftQueue
                                                                   : m_rightQueue;
    if (position < 0)
    {
        return nullptr;
    }
    else if (position >= m_N)
    {
        return &(q[m_N]);
    }

    return &(q[position]);
}
//==================================================================================
std::vector<CGraph::CVertex> &CGraph::getQueue(CGraph::EQueue queue)
{
    return queue == CGraph::EQueue::EQUEUE_LEFT ? m_leftQueue
                                                : m_rightQueue;
}
//==================================================================================
void CGraph::fillGraph(std::string leftQueue, std::string rightQueue)
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < m_N; ++j)
        {
            char c = (i == 0) ? leftQueue.at(j)
                              : rightQueue.at(j);
            if (c == 'x')
            {
                getQueue(static_cast<CGraph::EQueue>(i)).at(j).setSuitable(false);
                getQueue(static_cast<CGraph::EQueue>(i)).at(j).setState(CGraph::CVertex::EState::ESTATE_BLACK);
            }
            getQueue(static_cast<CGraph::EQueue>(i)).at(j).setPosition(j + 1);
        }
    }

    // terminal state
    m_leftQueue.at(m_N).setPosition(m_N + 1);
    m_rightQueue.at(m_N).setPosition(m_N + 1);
}
//==================================================================================
void CGraph::fillGraph()
{
    char c;
    // left and right queue
    for (int i = 0; i < 2; ++i)
    {
        // places
        for (int j = 0; j < m_N; ++j)
        {
            std::cin >> c;
            if (c == 'x')
            {
                getQueue(static_cast<CGraph::EQueue>(i)).at(j).setSuitable(false);
                getQueue(static_cast<CGraph::EQueue>(i)).at(j).setState(CGraph::CVertex::EState::ESTATE_BLACK);
            }
            getQueue(static_cast<CGraph::EQueue>(i)).at(j).setPosition(j + 1);
        }
    }

    // terminal state
    m_leftQueue.at(m_N).setPosition(m_N + 1);
    m_rightQueue.at(m_N).setPosition(m_N + 1);
}
//==================================================================================
void CGraph::constructNeighbours()
{
    for (int i = 0; i < m_N; ++i)
    {
        m_leftQueue[i].addNeighbour(getNeighbourReference(CGraph::EQueue::EQUEUE_LEFT, i - 1));
        m_leftQueue[i].addNeighbour(getNeighbourReference(CGraph::EQueue::EQUEUE_LEFT, i + 1));
        m_leftQueue[i].addNeighbour(getNeighbourReference(CGraph::EQueue::EQUEUE_RIGHT, i + m_K));

        m_rightQueue[i].addNeighbour(getNeighbourReference(CGraph::EQueue::EQUEUE_RIGHT, i - 1));
        m_rightQueue[i].addNeighbour(getNeighbourReference(CGraph::EQueue::EQUEUE_RIGHT, i + 1));
        m_rightQueue[i].addNeighbour(getNeighbourReference(CGraph::EQueue::EQUEUE_LEFT, i + m_K));
    }
}
//==================================================================================
void CGraph::BFS(CVertex *vertex)
{
    vertex->setState(CGraph::CVertex::EState::ESTATE_GRAY);
    vertex->setDistantion(0);

    std::queue<CVertex *> queueBFS;
    queueBFS.push(vertex);

    while (!queueBFS.empty())
    {
        CVertex *v = queueBFS.front();
        queueBFS.pop();

        for (auto w : v->getNeighbours())
        {
            if (w->getState() == CVertex::EState::ESTATE_WHITE && (v->getDistantion() + 1 < w->getPosition()))
            {
                w->setState(CVertex::EState::ESTATE_GRAY);
                w->setDistantion(v->getDistantion() + 1);
                queueBFS.push(w);
            }
        }
        v->setState(CVertex::EState::ESTATE_BLACK);
    }
}
//==================================================================================
int CGraph::findSolution(std::string leftQueue = std::string(), std::string rightQueue = std::string())
{
    (!leftQueue.empty() && !rightQueue.empty()) ? fillGraph(leftQueue, rightQueue)
                                                : fillGraph();
    constructNeighbours();
    BFS(&m_leftQueue[0]);

    if (m_leftQueue[m_N].getDistantion() == -1)
    {
        return m_rightQueue[m_N].getDistantion();
    }
    else if (m_rightQueue[m_N].getDistantion() == -1)
    {
        return m_leftQueue[m_N].getDistantion();
    }
    else
    {
        return m_leftQueue[m_N].getDistantion() < m_rightQueue[m_N].getDistantion() ? m_leftQueue[m_N].getDistantion()
                                                                                    : m_rightQueue[m_N].getDistantion();
    }
}
//==================================================================================
class CGraphTester
{
public:
    int findSolution(const int N, const int K, const std::string leftQueue, const std::string rightQueue)
    {
        CGraph g(N, K);
        return g.findSolution(leftQueue, rightQueue);
    }

    void startTest()
    {
        assert(findSolution(5, 2, "....x", ".xx.x") == 3);
        assert(findSolution(10, 4, ".xx.x...xx", "x.x....x..") == 4);
        assert(findSolution(5, 1, "..x..", "..xx.") == -1);
        assert(findSolution(7, 3, ".xxx.xx", "x...xxx") == -1);
        assert(findSolution(6, 3, ".xxx.x", "x...xx") == 2);
        assert(findSolution(10, 3, "...x.xxxxx", "......x...") == -1);
        assert(findSolution(5, 2, ".xx.x", "x..xx") == -1);
        assert(findSolution(10, 2, ".xxx.x.xxx", "xx.x...x..") == -1);
        assert(findSolution(10, 3, ".xxx...xxx", "xxx.xxx.xx") == 6);
        assert(findSolution(1, 1, ".", ".") == 1);
        assert(findSolution(5, 8, ".....", ".....") == 1);
        assert(findSolution(10, 3, "..xx...x..", "......x.xx") == 5);
        assert(findSolution(15, 4, ".xxxxxx.x...xxx", "xxx...xxx.x.xxx") == 5);
        assert(findSolution(19, 2, ".xx....x.x..x.xxx..", "xx...xx...xxx...xxx") == 12); 
    }
};

} // namespace khomcvla_ag1_1

#endif /* __PROGTEST_AG1_1__ */
//==================================================================================
int main(void)
{
    /* manual test */ 

    // int N;
    // int K;
    // std::cin >> N >> K;
    // khomcvla_ag1_1::CGraph g(N, K);
    // std::cout << g.findSolution() << std::endl;

    /* automatic test */
    
    khomcvla_ag1_1::CGraphTester gt;
    gt.startTest();

    return 0;
}