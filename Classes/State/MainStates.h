// [state2cpp] please include this file ins the declaration of class Main.

private:
    StateMachine _stateMachine;
public:
    void StartState();
    void ExecState();
    std::string DumpState() const;

private:
    void StateStart();
    void StateWaitStartGame();
    void StateStartGame();
    void StateGameOver();
    void StateWaitInitGame();
