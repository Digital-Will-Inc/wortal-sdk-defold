#include "wortal_iap.h"
#include "luautils.h"

#if defined(DM_PLATFORM_HTML5)

lua_Listener onIAPGetCatalogListener;
lua_Listener onIAPGetPurchasesListener;
lua_Listener onIAPMakePurchaseListener;
lua_Listener onIAPConsumePurchaseListener;

void WortalIAP::OnGetCatalog(const char* catalog, const char* error) {
    lua_State* L = onIAPGetCatalogListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onIAPGetCatalogListener);
    if (catalog) {
        lua_pushstring(L, catalog);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalIAP::OnGetPurchases(const char* purchases, const char* error) {
    lua_State* L = onIAPGetPurchasesListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onIAPGetPurchasesListener);
    if (purchases) {
        lua_pushstring(L, purchases);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalIAP::OnMakePurchase(const char* purchase, const char* error) {
    lua_State* L = onIAPMakePurchaseListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onIAPMakePurchaseListener);
    if (purchase) {
        lua_pushstring(L, purchase);
    }
    else {
        lua_pushnil(L);
    }
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

void WortalIAP::OnConsumePurchase(const int success, const char* error) {
    lua_State* L = onIAPConsumePurchaseListener.m_L;
    int top = lua_gettop(L);

    lua_pushlistener(L, onIAPConsumePurchaseListener);
    lua_pushboolean(L, success);
    if (error) {
        lua_pushstring(L, error);
    }
    else {
        lua_pushnil(L);
    }

    int ret = lua_pcall(L, 3, 0, 0);
    if (ret != 0) {
        lua_pop(L, 1);
    }

    assert(top == lua_gettop(L));
}

int WortalIAP::IsEnabled(lua_State* L) {
    int top = lua_gettop(L);

    int enabled = Wortal_iap_isEnabled();
    lua_pushboolean(L, enabled);

    assert(top + 1 == lua_gettop(L));
    return 1;
}

int WortalIAP::GetCatalogAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onIAPGetCatalogListener);
    Wortal_iap_getCatalogAsync(WortalIAP::OnGetCatalog);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalIAP::GetPurchasesAsync(lua_State* L) {
    int top = lua_gettop(L);

    luaL_checklistener(L, 1, onIAPGetPurchasesListener);
    Wortal_iap_getPurchasesAsync(WortalIAP::OnGetPurchases);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalIAP::MakePurchaseAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* purchaseConfig = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onIAPMakePurchaseListener);
    Wortal_iap_makePurchaseAsync(purchaseConfig, WortalIAP::OnMakePurchase);

    assert(top == lua_gettop(L));
    return 0;
}

int WortalIAP::ConsumePurchaseAsync(lua_State* L) {
    int top = lua_gettop(L);

    const char* token = luaL_checkstring(L, 1);
    luaL_checklistener(L, 2, onIAPConsumePurchaseListener);
    Wortal_iap_consumePurchaseAsync(token, WortalIAP::OnConsumePurchase);

    assert(top == lua_gettop(L));
    return 0;
}

#endif
