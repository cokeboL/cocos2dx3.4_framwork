/*
** Lua binding: Net
** Generated automatically by tolua++-1.0.92 on 09/15/14 18:03:19.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "Net/NetMgr.h"
#include "tolua_fix.h"

/* Exported function */
TOLUA_API int  tolua_Net_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CNetBean");
 tolua_usertype(tolua_S,"NetMgr");
 tolua_usertype(tolua_S,"uint32_t");
 tolua_usertype(tolua_S,"uint8_t");
}

/* method: getInstance of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_getInstance00
static int tolua_Net_NetMgr_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   NetMgr* tolua_ret = (NetMgr*)  NetMgr::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"NetMgr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendMessage of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_sendMessage00
static int tolua_Net_NetMgr_sendMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
	 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
	 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
	 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
	 !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  uint32_t len = ((uint32_t)  tolua_tonumber(tolua_S,2,0));
  uint8_t cmd = ((uint8_t)  tolua_tonumber(tolua_S,3,0));
  uint8_t action = ((uint8_t)  tolua_tonumber(tolua_S,4,0));
  char* pbMsg = ((char*)  tolua_tostring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendMessage'", NULL);
#endif
  {
   self->sendMessage(len,cmd,action,pbMsg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerCallBacks of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_registerCallBacks00
static int tolua_Net_NetMgr_registerCallBacks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,6,0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,4,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,5,"LUA_FUNCTION",0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,6,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  //int connCB = ((int)  tolua_tonumber(tolua_S,2,0));
  //int disconnCB = ((int)  tolua_tonumber(tolua_S,3,0));
  //int errCB = ((int)  tolua_tonumber(tolua_S,4,0));
  //int timeoutCB = ((int)  tolua_tonumber(tolua_S,5,0));
  //int msgCB = ((int)  tolua_tonumber(tolua_S,6,0));
  LUA_FUNCTION connCB = (  toluafix_ref_function(tolua_S,2,0));
  LUA_FUNCTION disconnCB = (  toluafix_ref_function(tolua_S,3,0));
  LUA_FUNCTION errCB = (  toluafix_ref_function(tolua_S,4,0));
  LUA_FUNCTION timeoutCB = (  toluafix_ref_function(tolua_S,5,0));
  LUA_FUNCTION msgCB = (  toluafix_ref_function(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerCallBacks'", NULL);
#endif
  {
   self->registerCallBacks(connCB,disconnCB,errCB,timeoutCB,msgCB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerCallBacks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: httpGet of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_httpGet00
static int tolua_Net_NetMgr_httpGet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,3,0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  std::string url = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  //int cbFunc = ((int)  tolua_tonumber(tolua_S,3,0));
  LUA_FUNCTION cbFunc = (  toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'httpGet'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->httpGet(url,cbFunc);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)url);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'httpGet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: httpPost of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_httpPost00
static int tolua_Net_NetMgr_httpPost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
	 !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     //!tolua_isnumber(tolua_S,4,0,&tolua_err) ||
	 !toluafix_isfunction(tolua_S,4,"LUA_FUNCTION",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  std::string url = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string data = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  //int cbFunc = ((int)  tolua_tonumber(tolua_S,4,0));
  LUA_FUNCTION cbFunc = (  toluafix_ref_function(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'httpPost'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->httpPost(url,data,cbFunc);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)url);
   tolua_pushcppstring(tolua_S,(const char*)data);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'httpGet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: connect of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_connect00
static int tolua_Net_NetMgr_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->connect(ip,port);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConnected of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_isConnected00
static int tolua_Net_NetMgr_isConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConnected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isConnected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_close00
static int tolua_Net_NetMgr_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  NetMgr */
#ifndef TOLUA_DISABLE_tolua_Net_NetMgr_close01
static int tolua_Net_NetMgr_close01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetMgr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NetMgr* self = (NetMgr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close();
  }
 }
 return 0;
tolua_lerror:
 return tolua_Net_NetMgr_close00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Net_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"NetMgr","NetMgr","CNetBean",NULL);
  tolua_beginmodule(tolua_S,"NetMgr");
   tolua_function(tolua_S,"getInstance",tolua_Net_NetMgr_getInstance00);
   tolua_function(tolua_S,"sendMessage",tolua_Net_NetMgr_sendMessage00);
   tolua_function(tolua_S,"registerCallBacks",tolua_Net_NetMgr_registerCallBacks00);
   tolua_function(tolua_S,"httpGet",tolua_Net_NetMgr_httpGet00);
   tolua_function(tolua_S,"httpPost",tolua_Net_NetMgr_httpPost00);
   tolua_function(tolua_S,"connect",tolua_Net_NetMgr_connect00);
   tolua_function(tolua_S,"isConnected",tolua_Net_NetMgr_isConnected00);
   tolua_function(tolua_S,"close",tolua_Net_NetMgr_close00);
   tolua_function(tolua_S,"close",tolua_Net_NetMgr_close01);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Net (lua_State* tolua_S) {
 return tolua_Net_open(tolua_S);
};
#endif

