#include <web/Kurulum_mod_sayfalar.h>

void Sunucu_mod_sayfalar()
{
    Serial.println("[Yerel Sunucu]: İnternet bağlantısı başlatılıyor.");

    //////////////Sayfa güncelleme scripleri için gerekli fonksiyonlar     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    server.on("/getCPUTemperature", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        float temperature = ((temprature_sens_read() - 32) / 1.8);
        request->send(200, "text/plain", String(temperature)); });

    server.on("/updateWorkingTime", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", Sistem_Calisma_Zamani); });

    server.on("/getDuty", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(duty)); });

    server.on("/getbekleme", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(bekleme)); });

    server.on("/getCurrent", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(current_sensor_value)); });

    server.on("/getTemp", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(int(Tc_ort))); });

    server.on("/getTemp_A", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(Tc_A)); });

    server.on("/getTemp_B", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(Tc_B)); });

    server.on("/getTemp_C", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(Tc_C)); });

    server.on("/getFreq", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(frekans)); });

    //////////////Kısa Linkler, sadece veri gonderiliyor.      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    server.on("/duytarttir", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  duty = duty + duty_artis;
                  request->send(200); // Başarılı bir istek durumunda 200 kodunu gönderir
              });

    server.on("/duytazalt", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  duty = duty - duty_artis;
                  request->send(200); // Başarılı bir istek durumunda 200 kodunu gönderir
              });

    server.on("/beklemearttir", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  bekleme = bekleme + bekleme_artis;
                  request->send(200); // Başarılı bir istek durumunda 200 kodunu gönderir
              });

    server.on("/beklemeazalt", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  bekleme = bekleme - bekleme_artis;
                  request->send(200); // Başarılı bir istek durumunda 200 kodunu gönderir
              });

    server.on("/restart", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  Serial.println();
                  Serial.println("[BILGI]: Sistem yeniden başlatılıyor..");
                  Serial.println();
                  Serial.println();
                  Serial.println();

                  Serial.flush();
                  ESP.restart();
                  request->send(200); // Başarılı bir istek durumunda 200 kodunu gönderir
              });

    //////////////main      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { String s = generateMainPageForm();
                request->send(200, "text/html", s); });

    //////////////update    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    server.on(
        "/update", HTTP_POST, [](AsyncWebServerRequest *request)
        {

                // Güncelleme işlemleri
                AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", generateUpdateInProgressForm());
                request->send(response); },
        [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
        {
            static size_t totalSize = 0;

            if (!index)
            {
                Update_Mod = 1;
                // vTaskSuspend(slave_func);

                totalSize = request->contentLength();
                Serial.println();
                Serial.println("[Bilgi]: Güncelleme başladı.");
                Serial.print("[Bilgi]: Dosya Boyutu: ");

                if (totalSize > 1023 and totalSize < 1048577)
                {
                    Serial.print(totalSize / 1024);
                    Serial.println(" kb");
                }
                else if (totalSize > 1048576)
                {
                    Serial.print(totalSize / 1024);
                    Serial.println(" mb");
                }

                // Serial.printf("[Bilgi]: Dosya Boyutu: %d byte\n", totalSize);

                if (!Update.begin(UPDATE_SIZE_UNKNOWN))
                {
                    Update.printError(Serial);
                }
            }
            if (Update.write(data, len) != len)
            {
                Update.printError(Serial);
            }
            if (final)
            {
                if (Update.end(true))
                {
                    Serial.println();
                    Serial.println("[Bilgi]: Güncelleme tamamlandı!");

                    // Güncelleme başarılı olduysa başarı sayfası göster
                    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", (Update.hasError()) ? generateUpdateFailForm(Update.errorString()) : generateUpdateSuccessForm());
                    request->send(response);
                    Serial.println("[Bilgi]: Cihaz Baştan Başlatılıyor..");
                    Serial.print("[Bilgi]: 3..");
                    delay(1000); // 1 saniye bekle
                    Serial.print(" 2..");
                    delay(1000); // 1 saniye bekle
                    Serial.println(" 1.. ");
                    delay(1000); // 1 saniye bekle
                    Serial.println();
                    Serial.println("[Bilgi]: Görüşürüz bb .ss :-) ");
                    Serial.println();
                    Serial.println();
                    Serial.flush();

                    Update_Mod = 2;
                    lastTime_Update = millis();
                }
                else
                {
                    Serial.println();
                    Serial.println("[HATA]: Güncelleme başarısız!");
                    Update.printError(Serial);
                    Update_Mod = 0;
                    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", generateUpdateFailForm(Update.errorString()));
                    request->send(response);
                }
            }
        });

    /////////////reset      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        for (int i = 0; i < last_eeprom; ++i) {
            EEPROM.write(i, 0);
        }
        EEPROM.commit();
        Serial.println("");
        Serial.println("[Bilgi]: Ayarlar Sıfırlandı. Yeniden yapılandırmak için cihazı yeniden başlatın. ");
        Serial.println("");

        String s = generateResetForm();
                request->send(200, "text/html", s); });
}
