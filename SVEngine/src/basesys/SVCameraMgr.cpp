//
// SVCameraMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVCameraMgr.h"
#include "../basesys/SVBasicSys.h"
#include "../node/SVCameraNode.h"
#include "../base/SVLock.h"

SVCameraMgr::SVCameraMgr(SVInst *_app)
:SVSysBase(_app) {
    m_subsysType = "SVCameraMgr";
    m_cameraLock = MakeSharedPtr<SVLock>();
}

SVCameraMgr::~SVCameraMgr() {
    m_cameraLock = nullptr;
}

void SVCameraMgr::init() {
    //相机
    m_mainCamera = MakeSharedPtr<SVCameraNode>(mApp);
}

void SVCameraMgr::destroy() {
    m_camerPool.clear();
    m_mainCamera = nullptr;
}

//更新
void SVCameraMgr::update(f32 dt) {
    if(m_mainCamera){
        m_mainCamera->update(dt);
        mApp->m_pGlobalParam->updateMainMat(m_mainCamera->getProjectMatObj(), m_mainCamera->getViewMatObj(), m_mainCamera->getVPMatObj());
    }
    m_cameraLock->lock();
    CAMERAPOOL::Iterator it = m_camerPool.begin();
    while ( it!=m_camerPool.end() ) {
        it->data->update(dt);
        it++;
    }
    m_cameraLock->unlock();
    
}

void SVCameraMgr::setMainCamera(SVCameraNodePtr _camera){
    if (_camera && _camera != m_mainCamera) {
        m_mainCamera = _camera;
    }
}

SVCameraNodePtr SVCameraMgr::getMainCamera(){
    return m_mainCamera;
}

void SVCameraMgr::addCamera(cptr8 _name, SVCameraNodePtr _camera){
    if (_camera == nullptr) {
        return;
    }
    if (hasCamera(_name)) {
        return;
    }
    m_cameraLock->lock();
    m_camerPool.append(SVString(_name), _camera);
    m_cameraLock->unlock();
}

bool SVCameraMgr::removeCamera(cptr8 _name){
    CAMERAPOOL::Iterator it = m_camerPool.find(SVString(_name));
    if( it!=m_camerPool.end() ) {
        m_camerPool.remove(it);
        return true;
    }
    return false;
}

SVCameraNodePtr SVCameraMgr::getCamera(cptr8 _name){
    CAMERAPOOL::Iterator it = m_camerPool.find(SVString(_name));
    if( it!=m_camerPool.end() ) {
        return it->data;
    }
    return nullptr;
}


bool SVCameraMgr::hasCamera(cptr8 _name) {
    CAMERAPOOL::Iterator it = m_camerPool.find(SVString(_name));
    if( it!=m_camerPool.end() ) {
        return true;
    }
    return false;
}

