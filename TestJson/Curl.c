#include <stdlib.h>
 
#include <curl/curl.h>
 
int main()
{
    CURL *curl = curl_easy_init();
    struct curl_slist *headers = NULL;
    if (curl) {
	const char *data =
	    "{\"jsonrpc\": \"1.0\", \"id\":\"curltest\", \"method\": \"getinfo\", \"params\": [] }";
 
	headers = curl_slist_append(headers, "content-type: text/plain;");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
 
	curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:9290/");
 
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(data));
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
 
	curl_easy_setopt(curl, CURLOPT_USERPWD,
			 "rpcUser:rpcPass");
 
	curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);
 
	curl_easy_perform(curl);
    }
    else printf("Error");
    return 0;
}

