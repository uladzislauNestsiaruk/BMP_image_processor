//
// Created by vlad on 29.10.23.
//

#ifndef CPP_HSE_APPLICATION_H
#define CPP_HSE_APPLICATION_H

class Application {

public:
    Application(int argc, char* argv[]);

    void Execute();

private:
    int argc_;
    char** argv_;
};

#endif  // CPP_HSE_APPLICATION_H
