Kullanıcı Grafiği ve Kırmızı-Siyah Ağaç Uygulaması
Bu proje, kullanıcılar ve arkadaşlık ilişkilerini yönetmek için bir veri yapısı uygulamasıdır. Kullanıcılar bir grafik yapısında temsil edilirken, kullanıcı ID'leri Kırmızı-Siyah Ağaç (Red-Black Tree) yapısında saklanır. Program, kullanıcı ekleme, arkadaşlık ekleme, kullanıcıları ve ilişkilerini yazdırma, belirli mesafedeki arkadaşları bulma, ortak arkadaşları bulma, toplulukları tespit etme, etki alanı hesaplama ve kullanıcı ID arama gibi işlevleri destekler.

Özellikler
Kullanıcı Ekleme: Kullanıcı ID'sini ekler ve grafikte yeni bir kullanıcı oluşturur.
Arkadaşlık Ekleme: İki kullanıcı arasında arkadaşlık ilişkisi ekler.
Kullanıcıları Yazdırma: Tüm kullanıcıları ve arkadaşlarını listeler.
DFS ile Arkadaş Arama: Derinlik öncelikli arama (DFS) kullanarak belirli mesafedeki arkadaşları bulur.
Ortak Arkadaşlar: İki kullanıcı arasındaki ortak arkadaşları bulur.
Topluluk Tespiti: Bağlı bileşenleri (toplulukları) bulur ve yazdırır.
Etki Alanı Hesaplama: Bir kullanıcının kaç kişiyi etkilediğini hesaplar.
Kullanıcı ID Arama (RB Tree): Kırmızı-Siyah Ağaç yapısında kullanıcı ID araması yapar.
Kurulum ve Çalıştırma
Gereksinimler: C dilini destekleyen bir derleyici (gcc gibi).
Derleme: Terminalde aşağıdaki komutu kullanarak programı derleyin:
Kopyala
gcc -o user_graph user_graph.c
Çalıştırma: Derlenmiş programı çalıştırmak için terminalde aşağıdaki komutu kullanın:
Kopyala
./user_graph
Kullanım
Program çalıştırıldığında aşağıdaki menü seçenekleri sunulacaktır:

1: Kullanıcı ekle
2: Arkadaşlık ekle
3: Kullanıcıları yazdır
4: DFS ile arkadaş ara
5: Ortak arkadaşlar
6: Toplulukları bul
7: Etki alanı hesapla
8: ID ara (RB Tree)
0: Çıkış
Her seçenek için gereken bilgileri girin ve işlemi gerçekleştirin.

Katkıda Bulunma
Bu projeye katkıda bulunmak isterseniz, lütfen bir pull request gönderin veya sorunları bildirin.

Lisans
Bu proje MIT lisansı altında lisanslanmıştır.

Bu README dosyası, kullanıcıların projeyi anlamalarına ve kullanmalarına yardımcı olacak şekilde tasarlanmıştır. İhtiyaçlarınıza göre özelleştirilebilir ve genişletilebilir.
