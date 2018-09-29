//
// SVPipleMain.cpp
// SVEngine
// Copyright 2017-2020
// 付一洲,尹龙,林龙飞,徐子昱,李晓帆,李达明
//

#include "SVPipleMain.h"
#include "SVPipleGridMgr.h"
#include "SVPipleBatUI.h"
#include "SVGameCommonEvent.h"
#include "SVQClickEvent.h"
#include "../third/rapidjson/document.h"
#include "../app/SVInst.h"
#include "../event/SVEventMgr.h"

using namespace sv;

SVPipleMain::SVPipleMain(SVInst*_app,cptr8 _respath)
:SVGameBase(_app) {
    m_respath = _respath;
    m_gametime = 80.0f;
    m_curgametime = 0.0f;
    m_playerCode = 1;
    m_mingci = 1;
    m_state = 0;
    m_pPipleMgr = nullptr;
    m_pBatUI = nullptr;
}

SVPipleMain::~SVPipleMain() {
}

void SVPipleMain::init(){
    enterex();
    m_curgametime = 0.0f;
    //
    m_pPipleMgr = new SVPipleGridMgr(mApp,this);
    m_pPipleMgr->init();
    //
    m_pBatUI = new SVPipleBatUI(mApp,this);
    m_pBatUI->init();
}

void SVPipleMain::destroy(){
    exitex();
    if(m_pBatUI){
        m_pBatUI->destroy();
        SAFE_DELETE(m_pBatUI);
    }
    if(m_pPipleMgr){
        m_pPipleMgr->destroy();
        SAFE_DELETE(m_pPipleMgr);
    }
}

void SVPipleMain::update(f32 _dt){
    if (m_state == 0){

    }else if(m_state == 1){
        m_curgametime += _dt;
        if(m_curgametime>=m_gametime){
            //游戏结束
            m_state = 3;
//            SVGameOver* t_event = new SVGameOver("");
//            mApp->m_pGlobalMgr->m_pEventMgr->pushEvent(t_event);
        }else{
            m_pPipleMgr->update(_dt,m_curgametime);
        }
    }else if(m_state == 3){
        m_pPipleMgr->update(_dt,m_curgametime);
    }
    //
    if(m_pBatUI){
        m_pBatUI->update(_dt);
    }
}

cptr8 SVPipleMain::getResPath(){
    return m_respath.c_str();
}

//解析字符串
void SVPipleMain::pushData(cptr8 _data){
//    RAPIDJSON_NAMESPACE::Document doc;
//    doc.Parse(_data);
//    if (doc.HasParseError()) {
//        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
//        SV_LOG_ERROR("rapidjson error code:%d \n", code);
//        return;
//    }
//    //游戏时间长度
//    if (doc.HasMember("gameLen")) {
//        RAPIDJSON_NAMESPACE::Value &t_gamelen = doc["gameLen"];
//        m_gametime = t_gamelen.GetFloat();
//    }
//    //主角色ID
//    if (doc.HasMember("playercode")) {
//        RAPIDJSON_NAMESPACE::Value &t_playercode = doc["playercode"];
//        m_playerCode = t_playercode.GetInt();
//    }
//    //角色名次
//    if (doc.HasMember("playermingci")) {
//        RAPIDJSON_NAMESPACE::Value &t_playemingci = doc["playermingci"];
//        m_mingci = t_playemingci.GetInt();
//    }
//    //玩家数据
//    if (doc.HasMember("players")) {
//        RAPIDJSON_NAMESPACE::Value &t_players = doc["players"];
//        if( t_players.IsArray() ){
//            for (u32 i = 0; i < t_players.Size(); i++) {
//                RAPIDJSON_NAMESPACE::Value &t_player = t_players[i];
//                s32 t_code = 0;
//                stringc t_name = "default";
//                if( t_player.HasMember("name") ){
//                    RAPIDJSON_NAMESPACE::Value &player_name = t_player["name"];
//                    t_name  = player_name.GetString();
//                }
//                if( t_player.HasMember("code") ){
//                    RAPIDJSON_NAMESPACE::Value &t_player_code = t_player["code"];
//                    t_code = t_player_code.GetInt();
//                }
//                if(m_pBatUI){
//                    m_pBatUI->setPersonData(t_code, t_name.c_str());
//                }
//            }
//        }
//    }
//    //分数
//    if (doc.HasMember("playerdatas")) {
//        RAPIDJSON_NAMESPACE::Value &t_playerdatas = doc["playerdatas"];
//        if( t_playerdatas.IsArray() ){
//            for (u32 i = 0; i < t_playerdatas.Size(); i++) {
//                RAPIDJSON_NAMESPACE::Value &t_data = t_playerdatas[i];
//                if(t_data.HasMember("name") && t_data.HasMember("score") ){
//                    RAPIDJSON_NAMESPACE::Value &t_playername = t_data["name"];
//                    RAPIDJSON_NAMESPACE::Value &t_playerscore = t_data["score"];
//                    stringc t_name = t_playername.GetString();
//                    s32 t_score = t_playerscore.GetInt();
//                    SVEventSetScore* t_event = new SVEventSetScore();
//                    t_event->m_score = t_score;
//                    t_event->m_playername = t_name;
//                    mApp->m_pGlobalMgr->m_pEventMgr->pushEvent(t_event);
//                }
//            }
//        }
//    }
}

bool SVPipleMain::procEvent(SVEvent *_event){
    SVEventGameStart* t_event_game_start = dynamic_cast<SVEventGameStart*>(_event);
    if(t_event_game_start){
        m_state = 1;    //游戏进行状态
    }
    SVGamePause* t_event_game_pause = dynamic_cast<SVGamePause*>(_event);
    if(t_event_game_pause){
        m_state = 2;    //游戏暂停状态
    }
    //设置游戏时间长度
    SVEventGameInfo* t_event_game_info = dynamic_cast<SVEventGameInfo*>(_event);
    if(t_event_game_info){
//        m_gametime = t_event_game_info->m_timelen;
//        m_playerCode = t_event_game_info->m_playerCode;
    }
    return true;
}



