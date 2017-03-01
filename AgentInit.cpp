#include"AgentImpl.h"
#include"BaseAgent.h"
#include"UserAgent.h"
#include"RandomAgent.h"
#include"QAgent.h"
#include"BoardClass.h"
#include"OseloSystem.h"

#include<StringPlus.h>

int BaseAgent::win = BoardClass::Cell_Empty;

using namespace std;

//コンストラクタ

//oseloにobj,my_colorにcolorを設定
BaseAgent::BaseAgent(const shared_ptr<OseloClass> &obj, const int &color)
	:base_pimpl(new Impl(obj,color)) {}

BaseAgent::~BaseAgent() = default;

//oseloにobj,my_colorにcolorを設定
UserAgent::UserAgent(const shared_ptr<OseloClass> &obj, const int &color)
	: BaseAgent(obj, color) {}

//oseloにobj,my_colorにcolorを設定
//putterをBoardSizeで初期化
RandomAgent::RandomAgent(const shared_ptr<OseloClass> &obj, const int &color)
	: BaseAgent(obj, color) {}
