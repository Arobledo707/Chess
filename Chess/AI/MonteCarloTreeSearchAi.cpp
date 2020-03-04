// MonteCarloTreeSearchAi.cpp
#include "MonteCarloTreeSearchAi.h"
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <iostream>

MonteCarloTreeSearchAi::MonteCarloTreeSearchAi(Board* pBoard)
    :m_pBoard(pBoard)
{
}

Move MonteCarloTreeSearchAi::FindBestMove()
{
    Node* pRootNode = new Node(new State(m_pBoard->CloneSelf(), m_playerNumber));
    Tree tree(pRootNode);

    int gamesPlayed = 0;
    while(gamesPlayed < kGamePlayCount) 
    {
        ++gamesPlayed;

        Node* pChosenNode = SelectNode(tree.GetRoot());
        if (pChosenNode->GetState()->GetBoard()->CheckForGameEnd() == 0) 
        {
            ExpandNode(pChosenNode);
        }
        Node* pNodeToExplore = pChosenNode;

        if (pChosenNode->GetChildren().size() > 0) 
        {
            pNodeToExplore = pChosenNode->GetRandomChild();
        }

        int playResult = SimulateRandomPlay(pNodeToExplore);
        BackPropogation(pNodeToExplore, playResult);
    }

    Node* pBestNode = pRootNode->GetChildren()[0];
    for(Node* pNode : pRootNode->GetChildren()) 
    {
        double newNodeScore = UctValue(pNode->GetParent()->GetState()->GetTimesVisited(), pNode->GetState()->GetWins(), pNode->GetState()->GetTimesVisited());
        double currNodeScore = UctValue(pNode->GetParent()->GetState()->GetTimesVisited(), pBestNode->GetState()->GetWins(), pBestNode->GetState()->GetTimesVisited());
        if (newNodeScore > currNodeScore)
        {
            pBestNode = pNode;
        }

    }

    return pBestNode->GetMove();
}

void MonteCarloTreeSearchAi::SetPlayerNumber(int playerNumber)
{
    m_playerNumber = playerNumber;
}


double MonteCarloTreeSearchAi::UctValue(int totalVisit, double nodeWinScore, int nodeVisit, double c)
{
    if (nodeVisit == 0)
    {
        return INT_MAX;
    }

    return (double)nodeWinScore / (double)nodeVisit + c * sqrt(log(totalVisit) / (double)nodeVisit);
}

Node* MonteCarloTreeSearchAi::SelectNode(Node* pRoot)
{
    Node* node = pRoot;

    while(node->GetChildren().size() > 0) 
    {
        node = FindBestNodeUCT(node);
    }
    return node;
}


Node* MonteCarloTreeSearchAi::FindBestNodeUCT(Node* pNode)
{
    int parentVisit = pNode->GetState()->GetTimesVisited();
    Node* pChosenNode = nullptr;
    double uctValue = -1;
    for(Node* pChild : pNode->GetChildren()) 
    {
        double newUctVal = UctValue(parentVisit, pChild->GetState()->GetWins(), pChild->GetState()->GetTimesVisited());
        if (newUctVal > uctValue)
        {
            uctValue = newUctVal;
            pChosenNode = pChild;
        }
    }

    return pChosenNode;
}



void MonteCarloTreeSearchAi::ExpandNode(Node* pNode)
{
    auto moves = pNode->GetState()->GetMoves();

    for (int i = 0; i < moves.size(); ++i) 
    {
        Board* pNewBoard = pNode->GetState()->GetBoard()->CloneSelf();
        State* newState = new State(pNewBoard, m_playerNumber);
        pNewBoard->MakeMove(moves[i]);
        Node* pChild = new Node(newState);
        pChild->SaveMove(moves[i]);
        pChild->SetParent(pNode);
        pNode->GetChildren().push_back(pChild);
    }
}

void MonteCarloTreeSearchAi::BackPropogation(Node* pNode, int playerNumber)
{
    Node* pTempNode = pNode;

    while(pTempNode != nullptr)
    {
        pTempNode->GetState()->IncrementVist();
        if (pTempNode->GetState()->GetPlayer() == playerNumber)
        {
            pTempNode->GetState()->IncrementWin();
        }
        else if(pTempNode->GetState()->GetPlayer() != playerNumber && playerNumber != 0)
        {
            pTempNode->GetState()->DecrementWin();
        }
        pTempNode = pTempNode->GetParent();
    }
}

int MonteCarloTreeSearchAi::SimulateRandomPlay(Node* pNode)
{
    Node* pTempNode = pNode;
    State* tempState = pTempNode->GetState();

    int boardStatus = tempState->GetBoard()->CheckForGameEnd();

    if (boardStatus == kPlayerWon)
    {
        return boardStatus;
    }

    while(boardStatus == 0 && tempState->GetMoves().size() > 0) 
    {
        tempState->RandomPlay();
        boardStatus = tempState->GetBoard()->CheckForGameEnd();
    }

    return boardStatus;
}


State::~State()
{
    delete m_pBoard;
    m_pBoard = nullptr;
}

void State::RandomPlay()
{
    auto moves = m_pBoard->GetAvailableMoves();
    if (moves.size() > 1)
    {
        m_pBoard->MakeMove(moves[rand() % ((moves.size() - 1))]);
    }
    else 
    {
        m_pBoard->MakeMove(moves[0]);
    }
}

Tree::~Tree()
{
    delete m_pRoot;
    m_pRoot = nullptr;
}

Node::~Node()
{
    delete m_pState;
    m_pState = nullptr;

    for (Node* m_pNode : m_pChildren) 
    {
        delete m_pNode;
        m_pNode = nullptr;
    }
}

Node * Node::GetRandomChild()
{
    return m_pChildren[rand() % (m_pChildren.size() - 1)];
}

