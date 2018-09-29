//
// SVEffectPackage.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVEffectPackage.h"
#include "../node/SVNode.h"
#include "../base/SVLock.h"
#include "../base/SVPreDeclare.h"
#include "../basesys/SVSceneMgr.h"
#include "../node/SVScene.h"
#include "../node/SVSpineNode.h"
#include "../core/SVSpine.h"
#include "../node/SVSpriteNode.h"
#include "../node/SVBitFontNode.h"
#include "../base/SVPreDeclare.h"

void spinenode_callback(SVSpineNodePtr _node,void* _obj,s32 _status) {
    SVEffectUnit *t_unit = (SVEffectUnit*)(_obj);
    if(_status == 2) {
        t_unit->setEnd(true);
    }else if(_status == 3) {
        t_unit->setEnd(true);
    }
}

SVEffectUnit::SVEffectUnit(SVInst* _app):SVGBase(_app){
    m_end = false;
}

SVEffectUnit::~SVEffectUnit(){
    
}

void SVEffectUnit::init(SVNodePtr _node){
    SVScenePtr t_scene = mApp->getSceneMgr()->getScene();
    if(_node && t_scene){
        m_node = _node;
        //这里先判断是spinenode的话就play，可以改成发个消息，然后所有的node一起播放。 晓帆
        SVSpineNodePtr t_spineNode = DYN_TO_SHAREPTR(SVSpineNode, m_node);
        if (t_spineNode) {
            cptr8 t_defAniName = t_spineNode->getCurAniName();
            t_spineNode->setSpineCallback(spinenode_callback, this);
            t_spineNode->setloop(true);
            t_spineNode->play(t_defAniName);
            m_end = false;
        }else{
            m_end = true;
        }
        t_scene->addNode(m_node);
    }
}

void SVEffectUnit::destroy(){
    if (m_node) {
        m_node->removeFromParent();
        m_node = nullptr;
    }
}

SVNodePtr SVEffectUnit::getNode(){
    return m_node;
}

void SVEffectUnit::setEnd(bool _end){
    m_end = _end;
}

bool SVEffectUnit::isEnd(){
    return m_end;
}

SVEffectPackage::SVEffectPackage(SVInst* _app)
:SVModuleBase(_app){
    m_lock = MakeSharedPtr<SVLock>();
    m_aniState = EFFECT_ANI_WAIT;
}

SVEffectPackage::~SVEffectPackage(){
    if (m_lock) {
        m_lock = nullptr;
    }
}

void SVEffectPackage::init(){
    SVModuleBase::init();
}

void SVEffectPackage::destroy(){
    m_lock->lock();
    for (s32 i = 0; i<m_effectUnitPool.size(); i++) {
        SVEffectUnitPtr t_unit = m_effectUnitPool[i];
        t_unit->destroy();
    }
    m_effectUnitPool.destroy();
    m_lock->unlock();
    SVModuleBase::destroy();
}

void SVEffectPackage::open(){
    SVModuleBase::open();
    m_aniState = EFFECT_ANI_BEGIN;
}

void SVEffectPackage::update(f32 _dt) {
    SVModuleBase::update(_dt);
    bool end = true;
    if (m_aniState == EFFECT_ANI_BEGIN) {
        for (s32 i = 0; i < m_effectUnitPool.size(); i++) {
            SVEffectUnitPtr t_unit = m_effectUnitPool[i];
            if (!t_unit->isEnd()) {
                end = false;
                break;
            }
        }
    }
    if (end && m_aniState == EFFECT_ANI_BEGIN) {
        m_aniState = EFFECT_ANI_END;
        if (m_cb) {
            SVString msg = SVString::format("effectpackageend %s",m_module_name.c_str());
            (*m_cb)(msg.c_str());
        }
    }
    
}

bool SVEffectPackage::procEvent(SVEventPtr _event) {
    return  true;
}

void SVEffectPackage::addEffectUnit(SVNodePtr _nodePtr){
    if (_nodePtr) {
        SVEffectUnitPtr effectUnit = MakeSharedPtr<SVEffectUnit>(mApp);
        effectUnit->init(_nodePtr);
        m_effectUnitPool.append(effectUnit);
    }
}


SVNodePtr SVEffectPackage::getNode(cptr8 _name){
    for (s32 i = 0; i < m_effectUnitPool.size(); i++) {
        SVEffectUnitPtr t_unit = m_effectUnitPool[i];
        if (strcmp(_name, t_unit->getNode()->getname()) == 0) {
            return t_unit->getNode();
        }
    }
    return nullptr;
}


