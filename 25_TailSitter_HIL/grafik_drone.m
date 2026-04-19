
portAdi = "COM5"; 
baudRate = 115200;


if ~isempty(serialportfind("PortName", portAdi))
    clear s;
end


s = serialport(portAdi, baudRate);
configureTerminator(s, "CR/LF"); 
flush(s);

disp("Bağlantı kuruldu. Veriler okunuyor...");
disp("Durdurmak için Command Window'a tıklayıp CTRL+C yapın.");


figure('Name', 'HIL Canlı Telemetri');
hLine = animatedline('Color', 'r', 'LineWidth', 2);
title('Sanal Drone Yüksekliği (Z Ekseni)');
xlabel('Zaman Adımı');
ylabel('Z Konumu');
grid on;

sayac = 1;


while true
    try
       
        gelenVeri = readline(s);
        
        
        veriler = str2double(split(gelenVeri, ","));
        
       
        if length(veriler) == 4 && ~any(isnan(veriler))
            
            addpoints(hLine, sayac, veriler(1));
            drawnow limitrate; 
            sayac = sayac + 1;
        end
    catch
        disp("Okuma durduruldu veya hata oluştu.");
        break;
    end
end