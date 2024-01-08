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
    Kurulum_Modu_Fonksiyonu();
}

void setup()
{
    pinMode(analog_buton_PIN, INPUT);
    pinMode(currretsensor_PIN, INPUT);
    pinMode(Encoder_A_PIN, INPUT);
    pinMode(Encoder_B_PIN, INPUT);
    pinMode(Hall_A_PIN, OUTPUT); // ŞİMDİLİK LEDİ TAKTIK
    pinMode(Hall_B_PIN, INPUT);
    pinMode(Hall_C_PIN, INPUT);
    pinMode(A_sensor_39_PIN, INPUT);

    pinMode(octopower_PIN, OUTPUT);
    /*
    pinMode(M_A_LIN_PIN, OUTPUT);
    pinMode(M_B_LIN_PIN, OUTPUT);
    pinMode(M_C_LIN_PIN, OUTPUT);
*/
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

    Baslatma_Fonksiyonlari();
}

void loop()
{
    if (Update_Mod != 1)
    {
        temperaturesfunction();
        buttonreadfunction();
        currentreadfunction();
        LCD_report_func();
        Surucu_Fonksiyonlari();
        Zaman_Guncellemesi();
        Seriport_Rapor();
    }
    if (Kurulum_Modu)
    {
        dnsServer.processNextRequest();
    }
}
