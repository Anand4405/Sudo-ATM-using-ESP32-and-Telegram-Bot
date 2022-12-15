#include <WiFi.h>

#include <HTTPClient.h>

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define id_wi "DESKTOP-2QKRA7D 8956"


#define UR_TOKEN_BOT "" // we are creating telegram bot.
#define pa_wi "00000000"
String g_sc_id = ""; // here we have to pass deploy id of ss.
#define ID_OF_CHAT "1302934180"  // this is unique of everyone so it will be accesible from particular's mobile.

const unsigned long time_bot = 1000; 

int ap = 1;
WiFiClientSecure secured_client;

UniversalTelegramBot bot(UR_TOKEN_BOT, secured_client);


unsigned long max_time_bot; // this is the time when scanning is done !!


int ab = 0;
int nk = 0;
int ur_balance = 15000;
int num_msgs()
{
int kgfh = bot.getUpdates(bot.last_message_received + 1);
return kgfh;
}
String yourdata()
{
  int kkkk = num_msgs();
  while(kkkk<1)
  {
     kkkk = num_msgs();
  }
  return bot.messages[0].text;
}

String fetching_data(int row,char col){
  if(WiFi.status()==WL_CONNECTED){
  String our_URL="https://script.google.com/macros/s/"+g_sc_id+"/exec?row="+row+"&col="+col+"&command=read";
  HTTPClient http;
  http.begin(our_URL.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int code_htp=http.GET();

  if(code_htp!=200){
      return "error in fetching the data 😥😥";
  }else{
    return http.getString();;
  }
  http.end();
  }else{
    return "Err 😥😥";
  }

}

void aapla_message(int total_msgs)
{
  Serial.print("aapla_message ");
  Serial.println(total_msgs);

  for (int i = 0; i < total_msgs; i++)
  {
    String imp_id = String(bot.messages[i].chat_id);
    if (imp_id != ID_OF_CHAT )
    {
      bot.sendMessage(imp_id,  "Unauthorized user", "");
    }
    else
    {
      String l = bot.messages[i].text;

      if (l == "/Begin")
      {
        String abc;
       abc = "Welcome to Anand's ATM. Hope U will enjoy our service 😁 \n";
      
        abc += "Please Enter your username : \n";
        bot.sendMessage(imp_id, abc, "Markdown");
      }
      l = yourdata();
String ayx = fetching_data(1,'A');
String pa;
      if (l == ayx)
      {
        
        bot.sendMessage(imp_id, "Enter your password: ", "");

        l = yourdata();
       ab = 1;
 
          pa = fetching_data(1,'B');

        }else {
          bot.sendMessage(imp_id, "Enter correct username ");
          return;
        }
      if (ab ==1  && pa==l)
      {
          bot.sendMessage(imp_id, "Enter  /credit for credit... /debit for debit \n.... /user for updating username... /pass for updating password...  /bal for balance checking...");
          l = yourdata();
          nk = 1;
      }
      else{
        bot.sendMessage(imp_id, "Enter correct paswword: ", "");
        return;
      }

      if (l=="/debit")
      {
        bot.sendMessage(imp_id, "Enter amount that you want to debit 💵💵 in multiples of 100 ", "");

        l = yourdata();
        if(l.toInt() > ur_balance)
        {
           bot.sendMessage(imp_id, "Your balance is not sufficient ❌❌❌ . Try again!!!");
           return;
        }
        if(l.toInt()%100)
        {
          bot.sendMessage(imp_id, "Please give amount in multiple of 100 😅😅. Try again!!! ");
          return;
        }
         if(l.toInt() <0)
        {
          bot.sendMessage(imp_id, "You entered negative amount..🙄🙄. Try again!!! ");
          return;
        }
        ur_balance = ur_balance - l.toInt();
     
        
      data_updation(ap,'D',l);
      Serial.println(ur_balance);
        data_updation(ap,'E',"0");
        
        ap += ap;
        bot.sendMessage(imp_id,l);
        data_updation(ap,'C',String(ur_balance));

      }
       if (l == "/credit")
      {
        bot.sendMessage(imp_id, "Enter amount to credit in multiples of 100 ");

        l = yourdata();
        if(l.toInt()%100)
        {
          bot.sendMessage(imp_id, "Please give amount in multiple of 100 ");
          return;
        }
         if(l.toInt() <0)
        {
          bot.sendMessage(imp_id, "Please give correct amount ");
          return;
        }
        
        ur_balance = ur_balance + l.toInt();
        Serial.println(ur_balance);
        String abc = String(ur_balance);
        
        data_updation(ap,'D',"0"); // here we are debiting so credit balance should be zero so we passesd zero in value.
           data_updation(ap,'C',String(ur_balance)); // Here we are updating our balance so that it will be easy for user
        bot.sendMessage(imp_id,"your available balance :"+abc); // we are showing availble balnce on screen. that is on telegram bot
        data_updation(ap,'E',l); //  now we are updating in our debit column.
       ap += ap;
        
      }
       if (l == "/balance")
      {
       
        bot.sendMessage(imp_id, "your acc balance is "+ String(ur_balance));
      }
      if(l =="/user")
      {
        bot.sendMessage(imp_id, "Enter your new username: ", "");
        l = yourdata();
        data_updation(1,'A',l);
      }
      if(l =="/pass")
      {
        bot.sendMessage(imp_id, "Enter your new password: ", "");
        l = yourdata();
        data_updation(1,'B',l);
      }
      
      
    }
  }
}

// String getrow()
// {

// }

String data_updation(int row,char col,String value)  // in this function we will update our data . first we access row and column then put our values.
{
  if(WiFi.status()==WL_CONNECTED){
  String our_URL="https://script.google.com/macros/s/"+g_sc_id+"/exec?row="+row+"&col="+col+"&value="+value+"&command=update";
  HTTPClient http;
  http.begin(our_URL.c_str()); // this is standard format of using http request
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int code_htp=http.GET();


  if(code_htp!=200){
      return "Err in updating your data !!😥";
  }else{
    return http.getString();
  }
  http.end();
  }else{
    return "Err 😥😥";
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("trying to connect wifi!! ");
  Serial.print(id_wi);
  WiFi.begin(id_wi, pa_wi);
   secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Not connecting try again");
    delay(500);
  }
  Serial.print("\n ur wifi is connected 🤩🤩 ....");
  
}

void loop()
{
  if (millis() - max_time_bot > time_bot)
  {
    int total_msgs = bot.getUpdates(bot.last_message_received + 1);

    while (total_msgs)
    {
      Serial.println("Our bot is responding 🤩🤩. ");
      aapla_message(total_msgs);
      total_msgs = bot.getUpdates(bot.last_message_received + 1);
    }

    max_time_bot = millis();
  }

}