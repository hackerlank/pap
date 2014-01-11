/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id macros.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 17:26:46
 * @uses 游戏中基本的宏定义（宏无命名空间的限制，所以不要放在命名空间中）
 *       可以单独包含该文件使用宏定义
 */
#ifndef PAP_COMMON_GAME_DEFINE_MACROS_H_
#define PAP_COMMON_GAME_DEFINE_MACROS_H_

#define COUNTRY_INVALID -1
#define JOB_INVALID -1
#define SEX_INVALID -1
#define GUILDID_INVALID -1
#define RESOURCE_INVALID -1
#define RULERID_INVALID -1
#define PRICE_INVALID 0
#define ITEMID_INVALID 0
#define ITEMPOS_INVALID -1
#define TIME_INVALID 0xFFFFFFFF
#define MENPAITYPE_INVALID 0
#define SOULTYPE_INVALID 0
#define BASE_BAGPOS 185
#define GUILDLEVEL_MAX 5 //公会最大等级
#define CHARACTER_ABILITYMAX 8 //角色最多的生活技能数量

#define SERVRENAME_MAX 32

/* account{ */
#define ACCOUNTLENGTH_MAX 50
#define MD5SIZE_MAX 32
/* account} */

/*pakcetid {*/  //网络包ID的范围定义
#define PACKETID_INVALID -1

//包ID范围为宏的 MIN + 1 --- MAX - 1
//MAX = MIN + LENGTH + 2
/*billing login { */
#define BILLINGLOGIN_PACKETID_MIN 0
#define BILLINGLOGIN_PACKETID_MAX (BILLINGLOGIN_PACKETID_MIN + 10 + 2)
#define BILLING_TOLOGIN_PACKETID_MIN (BILLINGLOGIN_PACKETID_MAX - 1)
#define BILLING_TOLOGIN_PACKETID_MAX (BILLING_TOLOGIN_PACKETID_MIN + 58 + 2)
#define LOGIN_TOBILLING_PACKETID_MIN (BILLING_TOLOGIN_PACKETID_MAX - 1)
#define LOGIN_TOBILLING_PACKETID_MAX (LOGIN_TOBILLING_PACKETID_MIN + 58 + 2)
/*billing login }*/

/*client login {*/
#define CLIENTLOGIN_PACKETID_MIN (LOGIN_TOBILLING_PACKETID_MAX - 1)
#define CLIENTLOGIN_PACKETID_MAX (LOGINCLIENT_PACKETID_MIN + 58 + 2)
#define LOGIN_TOCLIENT_PACKETID_MIN (LOGINCLIENT_PACKETID_MAX - 1)
#define LOGIN_TOCLIENT_PACKETID_MAX (LOGIN_TOCLIENT_PACKETID_MIN + 58 + 2)
#define CLIENT_TOLOGIN_PACKETID_MIN (LOGIN_TOCLIENT_PACKETID_MAX - 1)
#define CLIENT_TOLOGIN_PACKETID_MAX (CLIENT_TOLOGIN_PACKETID_MIN + 58 + 2)
/*login client }*/

/*login world {*/
#define LOGINWORLD_PACKETID_MIN (CLIENT_TOLOGIN_PACKETID_MAX - 1)
#define LOGINWORLD_PACKETID_MAX (LOGINWORLD_PACKETID_MIN + 58 + 2)
#define LOGIN_TOWORLD_PACKETID_MIN (LOGINWORLD_PACKETID_MAX - 1)
#define LOGIN_TOWORLD_PACKETID_MAX (LOGIN_TOWORLD_PACKETID_MIN + 58 + 2)
#define WORLD_TOLOGIN_PACKETID_MIN (LOGIN_TOWORLD_PACKETID_MAX - 1)
#define WORLD_TOLOGIN_PACKETID_MAX (WORLD_TOLOGIN_PACKETID_MIN + 58 + 2)
/*login world }*/

/*server world {*/
#define SERVERWORLD_PACKETID_MIN (WORLD_TOLOGIN_PACKETID_MAX - 1)
#define SERVERWORLD_PACKETID_MAX (WORLDSERVER_PACKETID_MIN + 58 + 2)
#define WORLD_TOSERVER_PACKETID_MIN (WORLDSERVER_PACKETID_MAX - 1)
#define WORLD_TOSERVER_PACKETID_MAX (WORLD_TOSERVER_PACKETID_MIN + 58 + 2)
#define SERVER_TOWORLD_PACKETID_MIN (WORLD_TOSERVER_PACKETID_MAX - 1)
#define SERVER_TOWORLD_PACKETID_MAX (SERVER_TOWORLD_PACKETID_MIN + 58 + 2)
/*server world }*/

/*client server {*/
#define CLIENTSERVER_PACKETID_MIN (SERVER_TOWORLD_PACKETID_MAX - 1)
#define CLIENTSERVER_PACKETID_MAX (CLIENTSERVER_PACKETID_MIN + 100 + 2)
#define CLIENT_TOSERVER_PACKETID_MIN (CLIENTSERVER_PACKETID_MAX - 1)
#define CLIENT_TOSERVER_PACKETID_MAX (CLIENT_TOSERVER_PACKETID_MIN + 1000 + 2)
#define SERVER_TOCLIENT_PACKETID_MIN (CLIENT_TOSERVER_PACKETID_MAX - 1)
#define SERVER_TOCLIENT_PACKETID_MAX (SERVER_TOCLIENT_PACKETID_MIN + 1000 + 2)
/*client server }*/

/*isvalid{ */
/**
#define ISVALID_BILLING_PACKETID(id) \
(BILLINGLOGIN_PACKETID_MIN < id && id < LOGIN_TOBILLING_PACKETID_MAX)
#define ISVALID_LOGIN_PACKETID(id) \
(BILLINGLOGIN_PACKETID_MIN < id && id < WORLD_TOLOGIN_PACKETID_MAX)
#define ISVALID_WORLD_PACKETID(id) \
(LOGINWORLD_PACKETID_MIN < id && id < SERVER_TOWORLD_PACKETID_MAX)
#define ISVALID_SERVER_PACKETID(id) \
(SERVERWORLD_PACKETID_MIN < id && id < SERVER_TOCLIENT_PACKETID_MAX)
#define ISVALID_CLIENT_PACKETID(id) \
((CLIENTLOGIN_PACKETID_MIN < id && id < CLIENT_TOLOGIN_PACKETID_MAX) || \
 (CLIENTSERVER_PACKETID_MIN < id && id < SERVER_TOCLIENT_PACKETID_MAX))
**/
/*isvalid} */

/*packetid }*/

#endif //PAP_COMMON_GAME_DEFINE_MACROS_H_