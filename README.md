# SoalShift_modul3_D06

## Soal 1 
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan

Contoh:

    ./faktorial 5 3 4
    3! = 6
    4! = 24
    5! = 120
    
Source Code : [Soal1](Soal1/)

### Penjelasan
1. setiap inputan dimasukkan dalam array
```  do {

      scanf("%d%c", &arr[i], &temp);

      i++;

  } while(temp != '\n');
```
2. lalu array disort
```
 for (i = 0; arr[i]!='\0'; ++i) 
        {
            for (j = i + 1; arr[j]!='\0'; ++j)
            {
                if (arr[i] > arr[j]) 
                {
                    x =  arr[i];
                    arr[i] = arr[j];
                    arr[j] = x;
                }
            }     
        }
```
3. setiap elemen array dicari faktorialnya dengan cara menggunakan thread, satu elemen array satu thread, perhitungan faktorial dilalkukan di dalam thread
```
void* tulis(void* args){
    unsigned long long fctr=1;
    struct Factorial*extract =(struct Factorial*)args;
	for(int i=1; i<=extract->val; ++i)
        {
            fctr = i*fctr;          
        }
    printf("[ Thread %d sukses dibuat | %d! Factorial = %llu ]\n",extract->val,extract->val,fctr);
   printf("\n");
}
```


## soal 2 <a name="soal_2"></a>
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:

- Terdapat 2 server: server penjual dan server pembeli
- 1 server hanya bisa terkoneksi dengan 1 client
- Server penjual dan server pembeli memiliki stok barang yang selalu sama
- Client yang terkoneksi ke server penjual hanya bisa menambah stok
- Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
- Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
- Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
- Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
- Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
- Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
- Server penjual akan mencetak stok saat ini setiap 5 detik sekali
- __Menggunakan thread, socket, shared memory__

Source Code : [Soal2](Soal2/)

### Penjelasan
Koneksi port harus dibedakan antara Pembeli dan Penjual
- Server pembeli
    1. Membuat socket.
    2. Membuat thread untuk display stock.
    3. Membuat thread untuk meng-handle send-receive dengan client.
- Server penjual
    1. Membuat socket.
    2. Membuat thread untuk meng-handle send-receive dengan client.
- Client pembeli
    1. Membuat socket.
    2. Menghubungkan dengan server.
    3. Menangani send-receive dengan Server.
- Client penjual
    1. Membuat socket.
    2. Menghubungkan dengan server.
    3. Menangani send-receive dengan Server.



## Soal 3 
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

- Terdapat 2 karakter Agmal dan Iraj
- Kedua karakter memiliki status yang unik
- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
- Iraj memiliki Spirit_Status, di awal program memiliki status 100
- Terdapat 3 Fitur utama
    - All Status, yaitu menampilkan status kedua sahabat

        Ex:
        
            Agmal WakeUp_Status = 75 
            Iraj Spirit_Status = 30
    - “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
    - “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
- Terdapat Kasus yang unik dimana:
    - Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
    - Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
- Program akan berhenti jika Salah Satu :
    - WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
    - Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)
- __Syarat Menggunakan Lebih dari 1 Thread__

Source Code : [Soal3](Soal3/)

### Penjelasn
1. Create thread untuk menghandle Agmal.
```
void* t_Agmal(void* args){
	while(1){
		if(strcmp(dsblfitur,"Agmal Ayo Bangun disabled 10 s")==0 && sleepcount==3){
			printf("Disable : Agmal Ayo Bangun (10 Sec)\n");
			sleep(10);
			agflag=0;
			sleepcount=0;
			printf("Enable : Agmal Ayo Bangun\n");
		}else{
			if(agflag==1){
				wakecount++;
				wakeup_status+=15;
				if(wakecount>3){
					wakecount=1;
				}
				if(wakecount==3){
					memset(dsblfitur,0,30);
					strcpy(dsblfitur,"Fitur Iraj Ayo Tidur disabled 10 s");
				}
			agflag=0;
			}
		}	
	}
}
```
2. Create thread untuk menghandle Iraj.
```
void* t_Iraj(void* args){
	while(1){
		if(strcmp(dsblfitur,"Fitur Iraj Ayo Tidur disabled 10 s")==0 && wakecount==3){
			printf("Disable : Iraj Ayo Tidur (10 Sec)\n");
			sleep(10);
			irflag=0;
			wakecount=0;
			printf("Enable : Iraj Ayo Tidur\n");
		}else{
			if(irflag==1){
				sleepcount++;
				spirit_status-=20;
				if(sleepcount>3){	
					sleepcount=1;
				}
				if(sleepcount==3){
					memset(dsblfitur,0,30);
					strcpy(dsblfitur,"Agmal Ayo Bangun disabled 10 s");
				}
			irflag=0;
			}
		}	
	}
}
```
3. Create loop untuk untuk menghandle input user.



## Soal 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 

__Dengan Syarat__ :
- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
- Ketika Mengekstrak file .zip juga harus secara bersama-sama
- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
- Wajib Menggunakan Multithreading
- Boleh menggunakan system

Source Code : [Soal4](Soal4/)

### Penjelasan
1. Membuat thread untuk menjalankan semua proses yang telah disebutkan
2. Membuat Direktori FolderProses1 dan Folder Proses2
```
    sprintf(command,"mkdir ~/Documents/FolderProses%d",extract->proc);
    system(command);
```
3. Menyimpan Lis proses pada ``ps -aux`` ,hanya 10 proses yang dilist dan disimpan dengan nama SimpanProses1.txt dan SimpanProses2.txt
```
    strcpy(command,"");
    sprintf(command,"ps aux --no-heading | head -%d  | tail -%d > ~/Documents/FolderProses%d/SimpanProses%d.txt",extract->high,extract->low,extract->proc,extract->proc);
    system(command);
```
4. Mengkompres file SimpanProses1.txt dan SimpanProses2.txt Menjadi KompresProses1.zip dan KompresProses2.zip, lalu menghapus file SimpanProses1.txt dan SimpanProses2.txt yang sudah di kompress tadi
```
    strcpy(command,"");
    sprintf(command,"zip -qmj ~/Documents/FolderProses%d/KompresProses%d ~/Documents/FolderProses%d/SimpanProses%d.txt",extract->proc,extract->proc,extract->proc,extract->proc);
    system(command);
```
5. Setalah Proses Kompres, lalu sleep selama 15 detik
```
  printf("Tunggu 15 Detik Untuk Unzip\n");
  for(int i=1; i<=15;i++){
	printf("%d\n",i);
	sleep(1);
  }
```
6. Create thread unzip, Setalah itu Mengunzip file KompresProses1.zip dan KompresProses2.zip
```
void* unzip(void* args){
    char command[100];
    struct Order*extract =(struct Order*)args;
    strcpy(command,"");
    sprintf(command,"unzip -qd ~/Documents/FolderProses%d ~/Documents/FolderProses%d/KompresProses%d.zip",extract->proc,extract->proc,extract->proc);
    //printf("%s",command);
    system(command);
} 
```
## Soal 5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
- Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
- Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
- Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
- Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
- Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
- Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
    - Pembeli (terintegrasi dengan game)
        - Dapat mengecek stok makanan yang ada di toko.
        - Jika stok ada, pembeli dapat membeli makanan.
    - Penjual (terpisah)
        - Bisa mengecek stok makanan yang ada di toko
        - Penjual dapat menambah stok makanan.

Spesifikasi program:
- Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
- Program terdiri dari 3 scene yaitu standby, battle, dan shop.
- Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit.

    Contoh :

        Standby Mode
        Health : [health status]
        Hunger : [hunger status]
        Hygiene : [hygiene status]
        Food left : [your food stock]
        Bath will be ready in [cooldown]s
        Choices
        1. Eat
        2. Bath
        3. Battle
        4. Shop
        5. Exit

- Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. 

    Contoh :

        Battle Mode
        Monster’s Health : [health status]
        Enemy’s Health : [enemy health status]
        Choices
        1. Attack
        2. Run

- Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. 

    Contoh :

        Shop Mode
        Shop food stock : [shop food stock]
        Your food stock : [your food stock]
        Choices
        1. Buy
        2. Back

- Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit.

    Contoh :

        Shop
        Food stock : [shop food stock]
        Choices
        1. Restock
        2. Exit

- Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

Source Code : [soal5](soal5/)

### Penjelasan :
- menyediakan fungsi untuk keypress

	```
	int mygetch(void)
	{
	    struct termios oldt, newt;
	    int ch;
	    tcgetattr( STDIN_FILENO, &oldt );
	    newt = oldt;
	    newt.c_lflag &= ~( ICANON | ECHO );
	    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	    ch = getchar();
	    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	    return ch;
	}
	```
	
- fungsi untuk menampilkan pilihan sesuai scene

	```
	void tampil(){
	    while(1){
		if (scene == 0) {
		    printf("Standby Mode\n");
		    printf("Health: %d \n", health_status);
		    printf("Hunger: %d \n", hunger_status);
		    printf("Hygiene: %d \n", hygiene_status);
		    printf("Health: %d \n", health_status);
		    printf("Food left : %d\n", my_food_stock);
		    printf("Bath will be ready in %ds \n", cooldown);
		    printf("Choiches\n");
		    printf("1. Eat\n");
		    printf("2. Bath\n");
		    printf("3. Battle\n");
		    printf("4. Shop\n");
		    printf("5. Exit\n");
		    scene = mygetch();
		}

		if (scene == 1){
		    printf("Battle Mode\n");
		    printf("Monster's Health: %d \n", health_status);
		    printf("Monster's Health %d \n", hunger_status);
		    printf("Choiches\n");
		    printf("1. Attack\n");
		    printf("2. Run\n");
		}

		if (scene == 2){
		    printf("Shop Mode\n");
		    printf("Shop Food Stock: %d \n", health_status);
		    printf("Your Food Stock: %d \n", hunger_status);
		    printf("Choiches\n");
		    printf("1. Buy\n");
		    printf("2. Back\n");
		}

		sleep(1);
		//system("cls");
	    }

	}
	```
	
- membuat fungsi untuk menjalankan mengurangi hunger_status setiap 10 detik
	```
	void hunger_kurang(){
	    while(1){
		if(1){
		    hunger_status = hunger_status - 5;
		    printf("hunger_status = %d\n", hunger_status);
		    sleep(10);
		}
	    }
	}
	```
