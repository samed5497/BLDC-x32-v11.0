#include <tanimlamalar.h>

boolean Baglanti_Kontrol()
{
    Serial.printf("\r\n[Wifi]: Bağlantı için bekleniyor..");

    int count = 0;
    while (count < 60)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println();
            Serial.printf("[WiFi]: Bağlantı Başarılı!\r\n[WiFi]: Yerel IP-Addresi: %s\r\n", WiFi.localIP().toString().c_str());
            Serial.printf("[WiFi]: MAC Addresi     : %s\r\n", WiFi.macAddress().c_str());

            return (true);
        }
        delay(500);
        Serial.print(".");
        count++;
    }
    Serial.println("");

    Serial.println("[WiFi]: Zaman aşımına uğrandı.");
    return false;
}

boolean Hafizadan_Yukle()
{
    Serial.println("[EEPROM]: Kayıtlı ağ okunuyor..");

    if (EEPROM.read(0) != 0)
    {
        for (int i = 0; i < 32; ++i)
        {
            char c = EEPROM.read(i);
            if (c == '\0')
            {
                break; // Null karakteri bulduğumuzda okumayı durdur
            }
            ssid_STA += c; // Karakteri String'e ekleyin
        }
        ssid_STA.trim();
        Serial.print("  SSID Adı  (");
        Serial.print(ssid_STA.length());
        Serial.print(") : ");
        Serial.println(ssid_STA);
        for (int i = 32; i < 96; ++i)
        {
            char c = EEPROM.read(i);
            if (c == '\0')
            {
                break; // Null karakteri bulduğumuzda okumayı durdur
            }
            pass_STA += c; // Karakteri String'e ekleyin
        }
        pass_STA.trim();
        Serial.print("  Şifre     (");
        Serial.print(pass_STA.length());
        Serial.print(") : ");
        Serial.println(pass_STA);

        for (int i = 96; i < 140; ++i)
        {
            char c = EEPROM.read(i);
            if (c == '\0')
            {
                break; // Null karakteri bulduğumuzda okumayı durdur
            }
            APP_KEY += c; // Karakteri String'e ekleyin
        }
        APP_KEY.trim();
        Serial.print("  APP_KEY   (");
        Serial.print(APP_KEY.length());
        Serial.print(") : ");
        Serial.println(APP_KEY);

        for (int i = 140; i < 250; ++i)
        {
            char c = EEPROM.read(i);
            if (c == '\0')
            {
                break; // Null karakteri bulduğumuzda okumayı durdur
            }
            APP_SECRET += c; // Karakteri String'e ekleyin
        }
        APP_SECRET.trim();

        Serial.print("  APP_SECRET(");
        Serial.print(APP_SECRET.length());
        Serial.print(") : ");
        Serial.println(APP_SECRET);

        for (int i = 250; i < last_eeprom; ++i)
        {
            char c = EEPROM.read(i);
            if (c == '\0')
            {
                break; // Null karakteri bulduğumuzda okumayı durdur
            }
            DEVICE_ID += c; // Karakteri String'e ekleyin
        }
        DEVICE_ID.trim();
        Serial.print("  DEVICE_ID (");
        Serial.print(DEVICE_ID.length());
        Serial.print(") : ");
        Serial.println(DEVICE_ID);
        /*
            if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
            {
              Serial.println("STA Failed to configure");
            }
        */
        WiFi.setSleep(false);
        WiFi.setAutoReconnect(true);
        WiFi.setHostname(hostname);
        WiFi.begin(ssid_STA.c_str(), pass_STA.c_str());

        return true;
    }
    else
    {
        Serial.println("[EEPROM]: Kayıtlı ağ bulunamadı!");
        return false;
    }
}

void Zaman_Guncellemesi()
{

    if (millis() - lastTime_Update > 2500 and Update_Mod == 2) // Güncelleme sonrası bilgilendirmeden sonra res at.
    {
        ESP.restart(); // Resetle
    }
}

void Sistem_Saat_Guncelleme()
{
    gecensure_sn = lastTime_DONGU / 1000;
    gecensure_dk = lastTime_DONGU / 60000;
    gecensure_saat = lastTime_DONGU / 3600000;
    gecensure_gun = lastTime_DONGU / 86400000;
    gecensure_hafta = lastTime_DONGU / 604800000;
    Sistem_Calisma_Zamani = "";
    Serial.println();
    Serial.print("---------------------------------  ");

    if (gecensure_hafta > 0)
    {
        // Serial.print(gecensure_hafta);
        // Serial.print(" hafta ");
        Sistem_Calisma_Zamani = String(gecensure_hafta) + " hafta ";
    }
    if (gecensure_gun > 0)
    {
        if (gecensure_gun >= 7)
        {
            // Serial.print(gecensure_gun - (gecensure_hafta * 7));
            Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_gun - (gecensure_hafta * 7)) + " gun ";
        }
        else
        {
            // Serial.print(gecensure_saat);
            Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_saat) + " gun ";
        }
        // Serial.print(" gun ");
    }
    if (gecensure_saat > 0)
    {
        if (gecensure_saat >= 24)
        {
            // Serial.print(gecensure_saat - (gecensure_gun * 24));
            Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_saat - (gecensure_gun * 24)) + " saat ";
        }
        else
        {
            // Serial.print(gecensure_saat);
            Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_saat) + " saat ";
        }
        // Serial.print(" saat ");
    }

    if (gecensure_dk > 0)
    {
        if (gecensure_dk >= 60)
        {
            // Serial.print(gecensure_dk - (gecensure_saat * 60));
            Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_dk - (gecensure_saat * 60)) + " dk ";
        }
        else
        {
            // Serial.print(gecensure_dk);
            Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_dk) + " dk ";
        }
        // Serial.print(" dk ");
    }

    if (gecensure_sn >= 60)
    {
        // Serial.print(gecensure_sn - (gecensure_dk * 60));
        Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_sn - (gecensure_dk * 60)) + " sn ";
    }
    else
    {
        // Serial.print(gecensure_sn);
        Sistem_Calisma_Zamani = Sistem_Calisma_Zamani + String(gecensure_sn) + " sn ";
        // Serial.print(" sn ");
    }

    // Sistem_Calisma_Zamani = String(String(gecensure_hafta) + " hafta " + String(gecensure_gun) + " gun " + String(gecensure_saat) + " saat " + String(gecensure_dk) + " dk " + String(gecensure_sn) + " sn");
    Serial.print(Sistem_Calisma_Zamani);

    Serial.println("  ---------------------------------");
    Serial.println("");
}

void Motor_PWM(byte pin, int kanal, int Motor_resolotion, int frekans, int duty)
{
    int resolation = pow(2, Motor_resolotion);
    duty = map(duty, 0, 100, 0, resolation);
    ledcSetup(kanal, frekans, Motor_resolotion);
    ledcAttachPin(pin, kanal);
    ledcWrite(kanal, duty);
}

void Motor_STOP(int kanal)
{
    ledcWrite(kanal, 0);
}

void temperaturesfunction()
{
    if (millis() - tempPreviousMillis >= sensorrefleshtime)
    {
        olcum_A = analogRead(NTC_A_PIN);
        olcum_A = ADC_LUT[(int)olcum_A];
        Vout_A = olcum_A * Vs / adcMax;
        Rt_A = R1 * Vout_A / (Vs - Vout_A);
        T_A = 1 / (1 / To + log(Rt_A / Ro) / Beta);
        Tc_A = T_A - 273.15;
        delay(1);

        olcum_B = analogRead(NTC_B_PIN);
        olcum_B = ADC_LUT[(int)olcum_B];
        Vout_B = olcum_B * Vs / adcMax;
        Rt_B = R1 * Vout_B / (Vs - Vout_B);
        T_B = 1 / (1 / To + log(Rt_B / Ro) / Beta);
        Tc_B = T_B - 273.15;
        delay(1);
        olcum_C = analogRead(NTC_C_PIN);
        olcum_C = ADC_LUT[(int)olcum_C];
        Vout_C = olcum_C * Vs / adcMax;
        Rt_C = R1 * Vout_C / (Vs - Vout_C);
        T_C = 1 / (1 / To + log(Rt_C / Ro) / Beta);
        Tc_C = T_C - 273.15;
        delay(1);

        Tc_ort = ((Tc_A + Tc_B + Tc_C) / 3);

        tempPreviousMillis = millis();
    }
}



void Adan_Bye()
{


    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, LOW);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, LOW);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, LOW);

    delayMicroseconds(musade);

    Motor_PWM(M_A_HIN_PIN, M_A_KAN_PIN, Motor_resolotion, frekans, duty);
    digitalWrite(M_A_LIN_PIN, HIGH);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, HIGH);
}

void Adan_Cye()
{


    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, LOW);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, LOW);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, LOW);

    delayMicroseconds(musade);

    Motor_PWM(M_A_HIN_PIN, M_A_KAN_PIN, Motor_resolotion, frekans, duty);
    digitalWrite(M_A_LIN_PIN, HIGH);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, HIGH);
}

void Bden_Cye()
{
  

    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, LOW);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, LOW);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, LOW);

    delayMicroseconds(musade);

    Motor_PWM(M_B_HIN_PIN, M_B_KAN_PIN, Motor_resolotion, frekans, duty);
    digitalWrite(M_B_LIN_PIN, HIGH);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, HIGH);
}

void Bden_Aya()
{


    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, LOW);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, LOW);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, LOW);

    delayMicroseconds(musade);

    Motor_PWM(M_B_HIN_PIN, M_B_KAN_PIN, Motor_resolotion, frekans, duty);
    digitalWrite(M_B_LIN_PIN, HIGH);

    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, HIGH);
}

void Cden_Aya()
{


    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, LOW);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, LOW);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, LOW);

    delayMicroseconds(musade);

    Motor_PWM(M_C_HIN_PIN, M_C_KAN_PIN, Motor_resolotion, frekans, duty);
    digitalWrite(M_C_LIN_PIN, HIGH);

    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, HIGH);
}

void Cden_Bye()
{
  

    Motor_STOP(M_A_KAN_PIN);
    digitalWrite(M_A_LIN_PIN, LOW);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, LOW);

    Motor_STOP(M_C_KAN_PIN);
    digitalWrite(M_C_LIN_PIN, LOW);

    delayMicroseconds(musade);

    Motor_PWM(M_C_HIN_PIN, M_C_KAN_PIN, Motor_resolotion, frekans, duty);
    digitalWrite(M_C_LIN_PIN, HIGH);

    Motor_STOP(M_B_KAN_PIN);
    digitalWrite(M_B_LIN_PIN, HIGH);
}


