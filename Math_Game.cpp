#include <bits/stdc++.h>
using namespace std;

enum enQuestionsLevel
{
    EasyLevel = 1,
    MedLevel = 2,
    HardLevel = 3,
    MixLevel = 4
};
enum enOperationType
{
    AddOp = 1,
    SubOp = 2,
    MultiOp = 3,
    DivOp = 4,
    MixOp = 5
};
struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enQuestionsLevel QuestionsLevel;
    enOperationType OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType opType;
    short NumberOfWrongAnswers = 0;
    short NumberOfCorrectAnswers = 0;
    bool isPass = false;
};
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
int Randomize(int from, int to)
{
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}
short QuizzesNumber()
{
    short GameRounds;
    do
    {
        cout << "Please how many quizzes\n";

        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}
string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
        case enOperationType::AddOp:
            return "+";
        case enOperationType::SubOp:
            return "-";
        case enOperationType::MultiOp:
            return "*";
        case enOperationType::DivOp:
            return "/";

        default:
            return "Mix";
    }
}
enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionsLevel = 0;
    do
    {
        cout << "Question Level [1] Easy [2] Med [3] Hard [4] Mix\n";
        cin >> QuestionsLevel;
    } while (QuestionsLevel < 1 || QuestionsLevel > 4);
    return (enQuestionsLevel)QuestionsLevel;
}
enOperationType ReadOpType()
{
    short OpType = 0;
    do
    {
        cout << "Operation Type [1] Add [2] Sub [3] Multi [4] Div [5] Mix\n";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}
enOperationType GetRandomOperationType()
{
    int Op = Randomize(1, 4);
    return (enOperationType)Op;
}
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
        case enOperationType::AddOp:
            return Number1 + Number2;
        case enOperationType::SubOp:
            return Number1 - Number2;
        case enOperationType::MultiOp:
            return Number1 * Number2;
        case enOperationType::DivOp:
            return Number1 / Number2;

        default:
            return Number1 + Number2;
    }
}
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;
    if (QuestionLevel == enQuestionsLevel::MixLevel)
    {
        QuestionLevel = (enQuestionsLevel)Randomize(1, 3);
    }
    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;
    switch (QuestionLevel)
    {
        case enQuestionsLevel::EasyLevel:
            Question.Number1 = Randomize(1, 10);
            Question.Number2 = Randomize(1, 10);

            Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
            Question.QuestionsLevel = QuestionLevel;
            return Question;
        case enQuestionsLevel::MedLevel:
            Question.Number1 = Randomize(10, 50);
            Question.Number2 = Randomize(10, 50);

            Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
            Question.QuestionsLevel = QuestionLevel;
            return Question;
        case enQuestionsLevel::HardLevel:
            Question.Number1 = Randomize(50, 100);
            Question.Number2 = Randomize(50, 100);

            Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
            Question.QuestionsLevel = QuestionLevel;
            return Question;
    }
    return Question;
}
void GenerateQuizQuestions(stQuiz &Quiz)
{
    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionsLevel, Quiz.opType);
    }
}
void PrintTheQuestion(stQuiz &Quiz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "]\n";
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quiz.QuestionList[QuestionNumber].OperationType);
    cout << "\n_______" << endl;
}
int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}
void SetScreenColor(bool Right)
{
    if (Right)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}
void CorrectTheQuestionAnswer(stQuiz &Quiz, short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;
        cout << "Wrong Answer :-(\n";
        cout << "The right answer is ";
        cout << Quiz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfCorrectAnswers++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswers(stQuiz &Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);
        Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quiz, QuestionNumber);
    }
    
    Quiz.isPass = (Quiz.NumberOfCorrectAnswers >= Quiz.NumberOfWrongAnswers);
}
string GetFinalResultText(bool Pass)
{
    if (Pass)
    {
        return "PASS :-)";
    }
    else
    {
        return "FAIL :-(";
    }
}
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = {"Easy", "Med", "Hard", "Mix"};
    return arrQuestionLevelText[QuestionLevel - 1];
}
void PrintQuizResults(stQuiz Quiz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Resutls is " << GetFinalResultText(Quiz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << Quiz.NumberOfQuestions << endl;
    cout << "Questions Level    : ";
    cout << GetQuestionLevelText(Quiz.QuestionsLevel) << endl;
    cout << "OpType             : " << GetOpTypeSymbol(Quiz.opType) << endl;
    cout << "Number of Right Answers: " << Quiz.NumberOfCorrectAnswers << endl;
    cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}
void PlayGame()
{
    stQuiz Quiz;
    Quiz.NumberOfQuestions = QuizzesNumber();
    Quiz.QuestionsLevel = ReadQuestionsLevel();
    Quiz.opType = ReadOpType();
    GenerateQuizQuestions(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizResults(Quiz);
}
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayGame();
        cout << "\n Do you want to play again? y/n";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}