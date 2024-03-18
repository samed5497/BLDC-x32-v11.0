#include <Baslangic_Fonksiyonlari.h>

void Baslatma_Fonksiyonlari() // Bootin fonksiyonu
{
    if (Hafizadan_Yukle())
    {
        if (Baglanti_Kontrol())
        {
            Kurulum_Modu = false;
            Web_Sunucu_Baslat();
            WiFi.softAPdisconnect(true);
            return;
        }
    }
    Kurulum_Modu = true;
    // sdfsdsfdsaf
    Kurulum_Modu_Fonksiyonu();
}

void setup()
{



    pinMode(currretsensor_PIN, INPUT);
    pinMode(octopower_PIN, OUTPUT);
    pinMode(M_A_LIN_PIN, OUTPUT);
    pinMode(M_B_LIN_PIN, OUTPUT);
    pinMode(M_C_LIN_PIN, OUTPUT);

    lcd.init(I2C_SDA, I2C_SCL);
    lcd.backlight();

    Serial.begin(115200);
    Serial.println("HMI Başlatılıyor. ");
    Serial.println();
    Serial.println();
    Serial.print(" >>> ");
    Serial.print(UYGULAMA);
    Serial.print(" / ");
    Serial.println(VERSIYON);
    Serial.printf("\r\n");
    EEPROM.begin(512);
    delay(10);
    lcd.setCursor(2, 0);
    lcd.print(UYGULAMA);
    lcd.setCursor(5, 2);
    lcd.print(VERSIYON);

    ilkakimdegeri = analogRead(currretsensor_PIN);

    Baslatma_Fonksiyonlari();

/*
     Motor_STOP(M_A_KAN_PIN);
      digitalWrite(M_A_LIN_PIN, LOW);
     Motor_STOP(M_B_KAN_PIN);
      digitalWrite(M_B_LIN_PIN, LOW);
     Motor_STOP(M_C_KAN_PIN);
      digitalWrite(M_C_LIN_PIN, LOW);
*/

}

void loop()
{
    if (Update_Mod != 1)
    {
        temperaturesfunction();
        currentreadfunction();
        Surucu_Fonksiyonlari();
        Zaman_Guncellemesi();
        // Sistem_Saat_Guncelleme();
        // buttonreadfunction();
        // LCD_report_func();
        // Seriport_Rapor();
    }
    if (Kurulum_Modu)
    {
        dnsServer.processNextRequest();
    }
}
