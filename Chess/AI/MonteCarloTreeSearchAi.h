    // MonteCarloTreeSearchAi.h
#pragma once
#include "../Chess/ChessBoard.h"
#include "../Constants/Constants.h"


class State 
{
public:
    State(Board* pBoard, int player) :m_pBoard(pBoard), m_player(player) {}
    ~State();

    Board* GetBoard() { return m_pBoard; }
    int GetPlayer() { return m_player; }
    int GetTimesVisited() { return m_timesVisited; }
    int GetWins() { return m_wins; }

    void IncrementVist() { ++m_timesVisited; }
    void IncrementWin() { ++m_wins; }
    void DecrementWin() { --m_wins; }

    std::vector<Move> GetMoves() { return m_pBoard->GetAvailableMoves(); }
    void RandomPlay();

private:
    Board* m_pBoard;
    int m_player;
    int m_timesVisited { 0 };
    int m_wins { 0 };
};

class Node 
{
public:
    Node(State* pState) : m_pState(pState) {}
    ~Node();

    void SetParent(Node* pNode) { m_pParent = pNode; }
    Node* GetParent() { return m_pParent; }
    std::vector<Node*>& GetChildren() { return m_pChildren; };

    State* GetState() { return m_pState; }
    Node* GetRandomChild();
    void SaveMove(Move move) { m_move = move; }
    Move GetMove() { return m_move; }
private:
    Move m_move;
    State* m_pState;
    Node* m_pParent { nullptr };
    std::vector<Node*> m_pChildren;
};

class Tree
{
public:
    Tree(Node* pNode) : m_pRoot(pNode){}
    Tree() {}
    ~Tree();

    Node* GetRoot() { return m_pRoot; }
    void SetRoot(Node* pNode) { m_pRoot = pNode; }
private:
    Node* m_pRoot { nullptr };
};

class MonteCarloTreeSearchAi
{
public:
    MonteCarloTreeSearchAi(Board* pBoard);
    Move FindBestMove();
    void SetBoard(Board* pBoard) { m_pBoard = pBoard; }
    void SetPlayerNumber(int playerNumber) { m_playerNumber = playerNumber; }
private:
    double UctValue(int totalVisit, double nodeWinScore, int nodeVisit, double c = 1.4);

    Node* SelectNode(Node* pRoot);
    Node* FindBestNodeUCT(Node* pNode);

    void ExpandNode(Node* pNode);
    void BackPropogation(Node* pNode, int playerNumber);
    int SimulateRandomPlay(Node* pNode);

private:
    Board* m_pBoard;
    const int kGamePlayCount = 10000;
    const int kPlayerWon = 1;

    Tree m_tree;
    int m_playerNumber = 2;

};
