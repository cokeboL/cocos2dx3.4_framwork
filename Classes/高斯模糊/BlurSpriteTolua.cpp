/*
** Lua binding: BlurSprite
** Generated automatically by tolua++-1.0.92 on 03/02/15 10:24:17.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "BlurSprite.h"

/* Exported function */
TOLUA_API int  tolua_BlurSprite_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Sprite");
 tolua_usertype(tolua_S,"Texture2D");
 tolua_usertype(tolua_S,"BlurSprite");
 tolua_usertype(tolua_S,"Rect");
}

/* method: initWithTexture of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_BlurSprite_BlurSprite_initWithTexture00
static int tolua_BlurSprite_BlurSprite_initWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Rect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BlurSprite* self = (BlurSprite*)  tolua_tousertype(tolua_S,1,0);
  Texture2D* texture = ((Texture2D*)  tolua_tousertype(tolua_S,2,0));
  const Rect* rect = ((const Rect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithTexture'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithTexture(texture,*rect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initGLProgram of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_BlurSprite_BlurSprite_initGLProgram00
static int tolua_BlurSprite_BlurSprite_initGLProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BlurSprite* self = (BlurSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initGLProgram'", NULL);
#endif
  {
   self->initGLProgram();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initGLProgram'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_BlurSprite_BlurSprite_create00
static int tolua_BlurSprite_BlurSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   BlurSprite* tolua_ret = (BlurSprite*)  BlurSprite::create(pszFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BlurSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_BlurSprite_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"BlurSprite","BlurSprite","cc.Sprite",NULL);
  tolua_beginmodule(tolua_S,"BlurSprite");
   tolua_function(tolua_S,"initWithTexture",tolua_BlurSprite_BlurSprite_initWithTexture00);
   tolua_function(tolua_S,"initGLProgram",tolua_BlurSprite_BlurSprite_initGLProgram00);
   tolua_function(tolua_S,"create",tolua_BlurSprite_BlurSprite_create00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_BlurSprite(lua_State* L) {
	 lua_getglobal(L, "_G");
	 if (lua_istable(L, -1))//stack:...,_G,
	 {
		 tolua_BlurSprite_open(L);
	 }
	 lua_pop(L, 1);
	 return 1;
 };
#endif