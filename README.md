# pipex

dup2 kullanımı 
/*
*	linux sistemlerde her proses için bir dosya betimleyici tablosu vardır.
*	Bu tablo içinde her gösterici açılmış bir dosyanın bilgilerini tutar ve
*	dosya nesnesi (file object) denilen bir veri yapısını işaret eder.
Örnek : Bir dosyaya ilişkin betimleyicinin başka bir dosya nesnesini gösterir duruma getirilmesine yönlendirme (redirection) denilmektedir.
FD . = sıradaki sayıyı temsil eeder
Process başladığındaki durum
FD 0		Std input		dosya nesnesi 0
FD 1		Std output		dosya nesnesi 1
FD 2		Std error		dosya nesnesi 1
FD .
FD .
FD .
open ile test adlı dosyayı açtıkdan sonraki durum.
FD 0		Std input		dosya nesnesi 0
FD 1		Std output		dosya nesnesi 1
FD 2		Std error		dosya nesnesi 1
FD 3						dosya nesnesi 2  <------ test
FD .
FD .
FD .
close ile FD 1 i kapatalım
FD 0		Std input		dosya nesnesi 0
FD 1										<------ dosya nesnesi göstermiyor artık buradaki FD
FD 2		Std error		dosya nesnesi 1
FD 3						dosya nesnesi 2	<------ test
FD .
FD .
FD .
Dup ile ilk boş olan FD a FD 3 ü kopyalıyalım.
FD 0		Std input		dosya nesnesi 0
FD 1						dosya nesnesi 2	<------ test
FD 2		Std error		dosya nesnesi 1
FD 3						dosya nesnesi 2	<------ test
FD .
FD .
FD .
artık aynı dosya nesnesini gösteriyorlar. stdoutput yerine açtığımız için terminale stdoutput üzerinden gidecek olan tüm çıktılar terminal yerine test dosyasının içerisine gidecek.
*	her dosya betimleyicisi(File Descriptor) bir anahtar değer işlevi görür işlem yapmak için gerekli bilgiler işletim sistemi tarafından dosya içine gönderilir
*	yukarıdaki örnekte FD1 ve FD3 aynı dosya nesnesini göstermekte bu dosya durumda iki dosya betimleyicisindende işlem yapabiliriz.
*	bir dosyayı birden fazla kez open komutu ile açabilir bu durumda farklı bir dosya nesnesi üretecek ve iki dosya nesnesinden de dosya ya erişebileceğiz
Örnek :
FD 0		Std input		dosya nesnesi 0
FD 1						dosya nesnesi 2	<------ test
FD 2		Std error		dosya nesnesi 1
FD 3						dosya nesnesi 2	<------ test
FD .
FD .
FD .
bu durumda open ile yeni bir dosya açar isek.
FD 0		Std input		dosya nesnesi 0
FD 1						dosya nesnesi 2	<------ test
FD 2		Std error		dosya nesnesi 1
FD 3						dosya nesnesi 2	<------ test
FD 4						dosya nesnesi 3	<------ test
FD .
FD .
FD .
*	close ile bir dosya betimleyicisi sonlandırıldığında eğer dosya nesnesini hala açık olan başka bir dosya betimleyicisi tarafından kullanılıyorsa dosya nesnesi kapatılmaz ama dosya nesnesinin içerisinde bulunan kullanım sayacı 1 düşürülür.
*	close ile bir dosya betimleyicisi sonlandırılması ve dup ile açılması temelde çalışsada aksama durumlarında veya çoklu çekirdek(multi thread)işlem yaparken sorunlara neden olabilemektedir bu nedenle dup 2 kullanırız.
*	dup2(param 1, param 2) ilk parametre olarak çuğaltıacak FDyı alır 2. parametre olarak  kapatılacak dosyayıalır. işlem sonunda param2 deki FD param 1 deki FD ile aynı dosya nesnesini gösterir.
Örnek :

FD 0		Std input		dosya nesnesi 0
FD 1		Std output		dosya nesnesi 1
FD 2		Std error		dosya nesnesi 1
FD .
FD .
FD .
open ile test adlı dosyayı açtıkdan sonraki durum.
FD 0		Std input		dosya nesnesi 0
FD 1		Std output		dosya nesnesi 1
FD 2		Std error		dosya nesnesi 1
FD 3						dosya nesnesi 2  <------ test
FD .
FD .
FD .
dup2 ile fd1 i kapatıp fd3 ile aynı dosya nesnesini göstertelim dup2(fd3, fd1)
FD 0		Std input		dosya nesnesi 0
FD 1						dosya nesnesi 2	<------ test
FD 2		Std error		dosya nesnesi 1
FD 3						dosya nesnesi 2	<------ test
FD .
FD .
FD .
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	fd = open("./dup/test", O_RDWR);
	printf("hello world\n");
	fprintf(stderr, "hello world\n");
	close(1);
	dup(fd);
	printf("aga naber");
}

// 0	start	dosya nesnesi 0
// 1	fd		dosya nesnesi 2 test
// 2	start	dosya nesnesi 1
// 3	fd		dosya nesnesi 2 test
// 4
// 4
// 56
