<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Game Tebak Angka</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            text-align: center;
            background-color: #f0f2f5;
            padding: 50px;
        }
        .game-container {
            background-color: #ffffff;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
            max-width: 400px;
            margin: 0 auto;
        }
        input[type="number"] {
            padding: 10px;
            margin: 10px 0;
            width: 80%;
            border: 1px solid #ccc;
            border-radius: 5px;
            font-size: 16px;
        }
        button {
            padding: 10px 20px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s ease;
        }
        button:hover {
            background-color: #0056b3;
        }
        #hasil {
            margin-top: 20px;
            font-weight: bold;
            min-height: 40px;
        }
    </style>
</head>
<body>

    <div class="game-container">
        <h1>Permainan Tebak Angka</h1>
        <p>Saya sudah memikirkan angka antara 1 sampai 100. Coba tebak!</p>
        
        <label for="tebakan">Masukkan Tebakan Anda:</label>
        <input type="number" id="tebakan" min="1" max="100" required>
        
        <button onclick="cekTebakan()">Tebak</button>
        <button onclick="resetGame()">Mulai Ulang</button>
        
        <p id="hasil">Tebakan Anda akan muncul di sini.</p>
        <p>Kesempatan: <span id="kesempatan">10</span></p>
    </div>

    <script>
        // --- Bagian JavaScript (Logika Game) ---

        // Variabel Global
        let angkaRahasia;
        let kesempatanSisa = 10;
        const maxKesempatan = 10;
        const minAngka = 1;
        const maxAngka = 100;

        // Fungsi untuk memulai atau mereset game
        function resetGame() {
            // 1. Menghasilkan angka acak antara minAngka dan maxAngka (1 - 100)
            angkaRahasia = Math.floor(Math.random() * (maxAngka - minAngka + 1)) + minAngka;
            
            // 2. Mengatur ulang kesempatan dan tampilan
            kesempatanSisa = maxKesempatan;
            document.getElementById('kesempatan').textContent = kesempatanSisa;
            document.getElementById('hasil').textContent = 'Silakan mulai menebak.';
            document.getElementById('tebakan').value = ''; // Kosongkan input
            
            console.log("Game dimulai. Angka rahasia (untuk debugging): " + angkaRahasia);
        }

        // Fungsi utama untuk memeriksa tebakan pemain
        function cekTebakan() {
            // Pastikan game sudah di-reset sebelum bermain
            if (!angkaRahasia) {
                resetGame();
            }

            // Dapatkan nilai tebakan dari input dan konversi ke integer
            const tebakanInput = document.getElementById('tebakan');
            const tebakan = parseInt(tebakanInput.value);
            const hasilElement = document.getElementById('hasil');

            // Validasi Input
            if (isNaN(tebakan) || tebakan < minAngka || tebakan > maxAngka) {
                hasilElement.textContent = `Masukkan angka yang valid antara ${minAngka} dan ${maxAngka}.`;
                return; // Hentikan fungsi jika input tidak valid
            }
            
            // Kurangi kesempatan
            kesempatanSisa--;
            document.getElementById('kesempatan').textContent = kesempatanSisa;

            // Logika Permainan
            if (tebakan === angkaRahasia) {
                // KASUS MENANG
                hasilElement.innerHTML = `<span style="color: green;">SELAMAT! Anda benar! Angka rahasianya adalah ${angkaRahasia}.</span>`;
                // Matikan input dan tombol tebak setelah menang
                document.getElementById('tebakan').disabled = true;
                // Panggil resetGame() saat tombol 'Mulai Ulang' diklik
            } else if (kesempatanSisa === 0) {
                // KASUS KALAH
                hasilElement.innerHTML = `<span style="color: red;">GAME OVER! Kesempatan Anda habis. Angka rahasianya adalah ${angkaRahasia}.</span>`;
                document.getElementById('tebakan').disabled = true;
            } else if (tebakan < angkaRahasia) {
                // KASUS TERLALU RENDAH
                hasilElement.textContent = 'Terlalu rendah! Coba lagi.';
            } else { // tebakan > angkaRahasia
                // KASUS TERLALU TINGGI
                hasilElement.textContent = 'Terlalu tinggi! Coba lagi.';
            }

            // Bersihkan input setelah menebak
            tebakanInput.value = '';
            tebakanInput.focus(); // Fokuskan kembali ke input
        }

        // Jalankan resetGame() saat halaman pertama kali dimuat
        window.onload = resetGame;
    </script>

</body>
</html>
