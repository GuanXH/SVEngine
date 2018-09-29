//
// SVFboObject.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFboObject.h"
#include "SVRenderScene.h"
#include "../rendercore/SVRenderMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTexMgr.h"
#include "../app/SVInst.h"
#include "../rendercore/SVGL/SVRResGL.h"
#include "../rendercore/SVMetal/SVRendererMetal.h"
#include "../rendercore/SVVulkan/SVRendererVK.h"
#include "../rendercore/SVGL/SVRendererGL.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVCameraMgr.h"
#include "../node/SVScene.h"
#include "../node/SVCameraNode.h"
//

SVFboObject::SVFboObject(SVInst *_app)
:SVRObjBase(_app){
}

SVFboObject::~SVFboObject() {
}

void SVFboObject::create(SVRendererBasePtr _renderer){
    SVRObjBase::create(_renderer);
    SVRendererBasePtr t_renderBasePtr = mApp->getRenderMgr()->getRenderer();
    SVRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<SVRendererGL>(t_renderBasePtr);
    if (t_renderGLPtr) {
        //渲染器类型E_RENDERER_GLES,
        m_objFBOPtr = MakeSharedPtr<SVRResGLFBO>(mApp);
        
    }
    SVRendererVKPtr t_rendeVKPtr = std::dynamic_pointer_cast<SVRendererVK>(t_renderBasePtr);
    if (t_rendeVKPtr) {
        //渲染器类型E_RENDERER_VUNKAN,
        
    }
    SVRendererMetalPtr t_rendeMetalPtr = std::dynamic_pointer_cast<SVRendererMetal>(t_renderBasePtr);
    if (t_rendeMetalPtr) {
        //渲染器类型E_RENDERER_METAL,
        
    }
    if (m_objFBOPtr) {
        m_objFBOPtr->create(_renderer);
    }
}

void SVFboObject::destroy(SVRendererBasePtr _renderer) {
    if (m_objFBOPtr) {
        m_objFBOPtr->destroy(_renderer);
    }
    SVRObjBase::destroy(_renderer);
}

void SVFboObject::refresh() {
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        t_tmp->refresh();
    }
}

void SVFboObject::bind() {
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        t_tmp->bind();
        SVCameraNodePtr t_camera = mApp->m_pGlobalMgr->m_pCameraMgr->getMainCamera();
        if (t_camera && t_camera->hasLinkFboObject(THIS_TO_SHAREPTR(SVFboObject))) {
            mApp->m_pGlobalParam->addToViewStack(m_mat_view);
            mApp->m_pGlobalParam->addToProjStack(m_mat_proj);
            mApp->m_pGlobalParam->addToVPStack(m_mat_vp);
        }
    }
}

void SVFboObject::clear(){
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        t_tmp->clear();
    }
}

void SVFboObject::unbind() {
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        t_tmp->unbind();
        SVCameraNodePtr t_camera = mApp->m_pGlobalMgr->m_pCameraMgr->getMainCamera();
        if (t_camera && t_camera->hasLinkFboObject(THIS_TO_SHAREPTR(SVFboObject))) {
            mApp->m_pGlobalParam->removeViewMat();
            mApp->m_pGlobalParam->removeProjMat();
            mApp->m_pGlobalParam->removeVPMat();
        }
    }
}

u32 SVFboObject::getFboID(){
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        return t_tmp->getFboID();
    }
    return 0;
}

u32 SVFboObject::getWidth(){
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        return t_tmp->getWidth();
    }
    return 0;
}

u32 SVFboObject::getHeight(){
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        return t_tmp->getHeight();
    }
    return 0;
}

bool SVFboObject::hasDepth(){
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        return t_tmp->hasDepth();
    }
    return 0;
}

bool SVFboObject::hasStencil(){
    SVRResGLFBOPtr t_tmp = std::dynamic_pointer_cast<SVRResGLFBO>(m_objFBOPtr);
    if (t_tmp) {
        return t_tmp->hasStencil();
    }
    return 0;
}

//
SVOutFboObject::SVOutFboObject(SVInst *_app,u32 _fboid)
:SVFboObject(_app){
    m_fboID = _fboid;
}

SVOutFboObject::~SVOutFboObject() {
    
}

void SVOutFboObject::create(SVRendererBasePtr _renderer){
    //外部设置的FBO 直接使用外部的就好
    SVRObjBase::create(_renderer);
    SVRendererBasePtr t_renderBasePtr = mApp->getRenderMgr()->getRenderer();
    SVRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<SVRendererGL>(t_renderBasePtr);
    if (t_renderGLPtr) {
        //渲染器类型E_RENDERER_GLES,
        m_objFBOPtr = MakeSharedPtr<SVRResGLOutFBO>(mApp, m_fboID);
        
    }
    SVRendererVKPtr t_rendeVKPtr = std::dynamic_pointer_cast<SVRendererVK>(t_renderBasePtr);
    if (t_rendeVKPtr) {
        //渲染器类型E_RENDERER_VUNKAN,
        
    }
    SVRendererMetalPtr t_rendeMetalPtr = std::dynamic_pointer_cast<SVRendererMetal>(t_renderBasePtr);
    if (t_rendeMetalPtr) {
        //渲染器类型E_RENDERER_METAL,
        
    }
    if(m_objFBOPtr){
        m_objFBOPtr->create(_renderer);
    }
}

void SVOutFboObject::destroy(SVRendererBasePtr _renderer){
    if (m_objFBOPtr) {
        m_objFBOPtr->destroy(_renderer);
    }
    SVRObjBase::destroy(_renderer);
}

