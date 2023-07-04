#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_HTML5)

class WortalIAP {
public:
    typedef void (*OnGetCatalogCallback)(const char* catalog, const char* error);
    typedef void (*OnGetPurchasesCallback)(const char* purchases, const char* error);
    typedef void (*OnMakePurchaseCallback)(const char* purchase, const char* error);
    typedef void (*OnConsumePurchaseCallback)(const int success, const char* error);

    static int IsEnabled(lua_State* L);
    static int GetCatalogAsync(lua_State* L);
    static int GetPurchasesAsync(lua_State* L);
    static int MakePurchaseAsync(lua_State* L);
    static int ConsumePurchaseAsync(lua_State* L);

private:
    static void OnGetCatalog(const char* catalog, const char* error);
    static void OnGetPurchases(const char* purchases, const char* error);
    static void OnMakePurchase(const char* purchase, const char* error);
    static void OnConsumePurchase(const int success, const char* error);
};

extern "C" {
    int Wortal_iap_isEnabled();
    void Wortal_iap_getCatalogAsync(WortalIAP::OnGetCatalogCallback callback);
    void Wortal_iap_getPurchasesAsync(WortalIAP::OnGetPurchasesCallback callback);
    void Wortal_iap_makePurchaseAsync(const char* purchaseConfig, WortalIAP::OnMakePurchaseCallback callback);
    void Wortal_iap_consumePurchaseAsync(const char* token, WortalIAP::OnConsumePurchaseCallback callback);
}

#endif
