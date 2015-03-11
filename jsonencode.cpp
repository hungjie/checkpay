#include "jsonencode.h"

#include <QJsonDocument>

JsonEncode::JsonEncode()
{

}

JsonEncode::~JsonEncode()
{

}

QJsonObject generateObject(QString const& func)
{
    QJsonObject object;

    if(func == "move"
            || func == "lbclick"
            || func == "timerinputvalue"
            || func == "waitLoadFinished"
            || func == "forfunc"
            || func == "scroll"
            || func == "sleep"
            || func == "randomscroll"
            || func == "randommove"
            || func == "randommbclick"
            || func == "randomscrollandmoveandmbclick"
            )
    {
        object.insert("func", func);
    }

    return object;
}

bool JsonEncode::parser(const QString &arg)
{
    fromArg(arg);

    QJsonObject move = generateObject("move");
    QJsonObject parms0;
    parms0.insert("id", QString("J_TSearchForm"));
    QJsonObject parms0offset;
    parms0offset.insert("left",10);
    parms0offset.insert("top",10);
    parms0.insert("offset", parms0offset);
    move.insert("parms",parms0);
    array_.push_back(move);

    QJsonObject lbclick = generateObject("lbclick");
    QJsonObject parms1;
    lbclick.insert("parms",parms1);
    array_.push_back(lbclick);

    QJsonObject timerinputvalue = generateObject("timerinputvalue");
    QJsonObject parms2;
    parms2.insert("cur_input", "");
    parms2.insert("time", 1000);
    QJsonArray parms2input_array;
    parms2input_array.push_back("女");
    parms2input_array.push_back("装");
    parms2.insert("input_array", parms2input_array);
    parms2.insert("input_id", "q");
    timerinputvalue.insert("parms", parms2);
    array_.push_back(timerinputvalue);

    QJsonObject move3 = generateObject("move");
    QJsonObject parms3;
    QJsonObject parms3id_class;
    parms3id_class.insert("id", "J_TSearchForm");
    parms3id_class.insert("class", "btn-search");
    parms3.insert("id_class", parms3id_class);
    QJsonObject parms3offset;
    parms3offset.insert("left",10);
    parms3offset.insert("top",10);
    parms3.insert("offset", parms3offset);
    move3.insert("parms",parms3);
    array_.push_back(move3);

    QJsonObject lbclick4 = generateObject("lbclick");
    QJsonObject parms4;
    lbclick4.insert("parms",parms4);
    array_.push_back(lbclick4);

    QJsonObject waitLoadFinished5 = generateObject("waitLoadFinished");
    QJsonObject parms5;
    parms5.insert("times", 10);
    parms5.insert("tab_index", 0);
    waitLoadFinished5.insert("parms", parms5);
    array_.push_back(waitLoadFinished5);

    QJsonObject actionsleepadd = generateObject("sleep");
    QJsonObject actionsleep1parmsadd;
    actionsleep1parmsadd.insert("mtime", 2000);
    actionsleepadd.insert("parms", actionsleep1parmsadd);
    array_.push_back(actionsleepadd);

    QJsonObject forfunc6 = generateObject("forfunc");
    QJsonObject parms6;
    parms6.insert("limit_times", 5);
    parms6.insert("cur_times", 0);
    parms6.insert("end_status", false);
    parms6.insert("end_condition", "foundelementid");
    QJsonObject parms6endparms;
    parms6endparms.insert("id", "J_Itemlist_Pic_41581154377");
    QJsonObject parms6randomclassid;
    parms6randomclassid.insert("id","mainsrp-itemlist");
    parms6randomclassid.insert("class","pic-box-inner");
    parms6endparms.insert("random_class_id", parms6randomclassid);
    parms6.insert("end_parms", parms6endparms);
    parms6.insert("action_index", 0);


    QJsonArray QJsonArrayActions;

    /*

    QJsonObject actionscroll01 = generateObject("randomscroll");
    QJsonObject actionparms01;
    actionscroll01.insert("parms", actionparms01);

    QJsonArrayActions.push_back(actionscroll01);

    QJsonObject actionmove02 = generateObject("randommove");
    QJsonObject actionparms02;
    actionmove02.insert("parms", actionparms02);

    QJsonArrayActions.push_back(actionmove02);

    QJsonObject actionmbclick03 = generateObject("randommbclick");
    QJsonObject actionparms03;
    actionmbclick03.insert("parms", actionparms03);

    QJsonArrayActions.push_back(actionmbclick03);

    */

    QJsonObject actionrandomSMC = generateObject("randomscrollandmoveandmbclick");
    QJsonObject actionrandomSMC_parms;
    actionrandomSMC_parms.insert("id", "mainsrp-itemlist");
    actionrandomSMC_parms.insert("class_name", "pic-box-inner");
    actionrandomSMC_parms.insert("cur_time", 0);
    actionrandomSMC_parms.insert("times", 2);
    actionrandomSMC.insert("parms", actionrandomSMC_parms);

    QJsonArrayActions.push_back(actionrandomSMC);

    QJsonObject actionscroll0 = generateObject("scroll");
    QJsonObject actionparms0;
    QJsonObject actionparms0id_class;
    actionparms0id_class.insert("id", "mainsrp-pager");
    actionparms0id_class.insert("class", "J_Ajax num icon-tag");
    actionparms0id_class.insert("class_index", -1);
    actionparms0.insert("id_class", actionparms0id_class);
    QJsonObject actionparms0offset;
    actionparms0offset.insert("left", -100);
    actionparms0offset.insert("top", -100);
    actionparms0.insert("offset", actionparms0offset);
    actionscroll0.insert("parms", actionparms0);

    QJsonArrayActions.push_back(actionscroll0);

    QJsonObject actionsleep1 = generateObject("sleep");
    QJsonObject actionsleep1parms;
    actionsleep1parms.insert("mtime", 2000);
    actionsleep1.insert("parms", actionsleep1parms);

    QJsonArrayActions.push_back(actionsleep1);

    QJsonObject actionmove2 = generateObject("move");
    QJsonObject actionmove2parms;
    QJsonObject actionmove2id_class;
    actionmove2id_class.insert("id", "mainsrp-pager");
    actionmove2id_class.insert("class", "J_Ajax num icon-tag");
    actionmove2id_class.insert("class_index", -1);

    actionmove2parms.insert("id_class", actionmove2id_class);
    QJsonObject actionmove2offset;
    actionmove2offset.insert("left",10);
    actionmove2offset.insert("top",10);
    actionmove2parms.insert("offset", actionmove2offset);
    actionmove2.insert("parms",actionmove2parms);

    QJsonArrayActions.push_back(actionmove2);

    QJsonArrayActions.push_back(lbclick4);

    QJsonArrayActions.push_back(waitLoadFinished5);

    parms6.insert("actions", QJsonArrayActions);

    forfunc6.insert("parms", parms6);


    array_.push_back(forfunc6);
}

QString JsonEncode::toJsonString()
{
    QJsonDocument document;
    document.setArray(array_);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);

    return "var main_script = " + json_str + ";";
}

void JsonEncode::fromArg(const QString &arg)
{

}

