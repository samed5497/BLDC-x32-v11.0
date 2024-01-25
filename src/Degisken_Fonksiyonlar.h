#include <Temel_Fonksiyonlar.h>

void Seriport_Rapor() // sure = ms
{
    if (millis() - lastTime_DONGU > seriport_sure and Update_Mod == 0 and SeriPort_Durum == 1)
    {
        Sistem_Saat_Guncelleme();

        Serial.println(" ");
        Serial.print(" ~ Octo Pwr           = ");
        Serial.println(system_power);
        Serial.print(" ~ Duty               = %");
        Serial.println(duty);
        Serial.print(" ~ Bekleme            = ");
        Serial.print(bekleme);
        Serial.println(" micro sn ");

        Serial.print(" ~ Sıcaklık           = ");
        Serial.print(Tc_ort);
        Serial.print("°C / A: ");
        Serial.print(Tc_A);
        Serial.print("°C - B: ");
        Serial.print(Tc_B);
        Serial.print("°C - C: ");
        Serial.print(Tc_C);
        Serial.println("°C");

        Serial.print(" ~ Akım               = ");
        Serial.print(current_sensor_value);
        Serial.println(" mA");

        Serial.print(" ~ Bağlı Wi-Fi Ağı    = ");
        Serial.println(ssid_STA);

        Serial.print(" ~ IP Adresi          = ");
        Serial.println(WiFi.localIP().toString());

        Serial.print(" ~ MAC Adresi         = ");
        Serial.println(WiFi.macAddress());
        Serial.print(" ~ CPU Sıcaklığı      = ");
        Serial.print((temprature_sens_read() - 32) / 1.8);
        Serial.println(" C");
        lastTime_DONGU = millis();
    }
}

void currentreadfunction()
{
    if (millis() - currentPreviousMillis >= sensorrefleshtime)
    {
        current_sensor_value = analogRead(currretsensor_PIN);

        currentPreviousMillis = millis();
    }
}


void buttonreadfunction()
{
    //----------X1---------
    // 1074----açma kapama    1150-1000
    // 1233----duty azalma    1400-1160
    // 1560----bekleme artma  1900-1410
    // 2145----duty artma     2500-1910
    // 4095----bekleme azalma 5000-3000

    //----------X2---------
    // 1295----açma kapama    1390-1100
    // 1580----duty azalma    1690-1400
    // 1870----bekleme artma  1940-1700
    // 2105----duty artma     2200-1950
    // 4095----bekleme azalma 5000-3000

/*
    Buton = analogRead(analog_buton_PIN);

    if (Buton > 800 && (millis() - lastDebounceTime) > debounceDelay)
    {
        lastDebounceTime = millis();
        if (1150 >= Buton && Buton > 810 && system_power == false)
        {
            digitalWrite(octopower_PIN, HIGH);
            system_power = true;
            digitalWrite(Hall_A_PIN, HIGH);
            Serial.println();
            Serial.println("[KONTROL] OCTO Power ON");
        }
        else if (1150 >= Buton && Buton > 900 && system_power == true)
        {
            digitalWrite(octopower_PIN, LOW);
            system_power = false;
            digitalWrite(Hall_A_PIN, LOW);
            Serial.println();
            Serial.println("[KONTROL] OCTO Power OFF");
        }

        else if (2500 >= Buton && Buton > 1910)
        {
            duty = duty + duty_artis;
            
            Serial.println();
            Serial.print("[KONTROL] Duty: ");
            Serial.println(duty);
            
        }
        else if (1400 >= Buton && Buton > 1160)
        {
            duty = duty - duty_artis;
            if (duty < 0)
            {
                duty = 0;
            }
            
            Serial.println();
            Serial.print("[KONTROL] Duty: ");
            Serial.println(duty);
            
        }

        else if (1900 >= Buton && Buton > 1410)
        {
            bekleme = bekleme + bekleme_artis;
            if (bekleme < 0)
            {
                bekleme = 0;
            }
            
            Serial.println();
            Serial.print("[KONTROL] Bekleme: ");
            Serial.println(bekleme);
            
        }
        else if (5000 >= Buton && Buton > 3000)
        {
            bekleme = bekleme - bekleme_artis;
            
            Serial.println();
            Serial.print("[KONTROL] Bekleme: ");
            Serial.println(bekleme);
            
        }
    }
    */
}

void LCD_report_func()
{
    lcd.setCursor(0, 0);
    lcd.print("% ");
    lcd.print(duty);
    lcd.print("  ");
    lcd.setCursor(9, 0);
    lcd.print("/ ");
    lcd.setCursor(11, 0);
    lcd.print(bekleme);
    lcd.print(" us");

    lcd.setCursor(5, 1);
    lcd.print("Sys / ");

    if (system_power == true)
    {
        lcd.print(" ON  ");
    }
    else if (system_power == false)
    {
        lcd.print(" OFF ");
    }

    lcd.setCursor(1, 2);
    lcd.print("A:");
    lcd.print(Tc_A);
    lcd.print(" / B:");
    lcd.print(Tc_B);
    lcd.print(" / C:");
    lcd.print(Tc_C);

    lcd.setCursor(0, 3);
    lcd.print("I= ");
    lcd.print(current_sensor_value);
    lcd.print(" mA");
    lcd.setCursor(11, 3);
    lcd.print("B1= ");
    if (Buton > 0)
    {
        lcd.print(Buton);
    }
    else
    {
        lcd.print("    ");
    }
}

void Surucu_Fonksiyonlari()
{
/*
    if (Tc_A > 200 or Tc_B > 200 or Tc_C > 200 or Tc_ort > 150)
    {
        system_power = false;

        Motor_STOP(M_A_KAN_PIN);
        digitalWrite(M_A_LIN_PIN, LOW);
        Motor_STOP(M_B_KAN_PIN);
        digitalWrite(M_B_LIN_PIN, LOW);
        Motor_STOP(M_C_KAN_PIN);
        digitalWrite(M_C_LIN_PIN, LOW);

        Serial.println("[ALARM]: Sistem Yüksek Isıdan Dolayı Koruma Amaçlı Devre Dışı Bırakıldı!");
    }
*/
    if (system_power == true)
    {
        Adan_Bye();
        delayMicroseconds(bekleme);
        Adan_Cye();
        delayMicroseconds(bekleme);
        Bden_Cye();
        delayMicroseconds(bekleme);
        Bden_Aya();
        delayMicroseconds(bekleme);
        Cden_Aya();
        delayMicroseconds(bekleme);
        Cden_Bye();
        delayMicroseconds(bekleme);
    }
}