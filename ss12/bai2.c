#include <stdio.h>
#include <string.h>

#define MAX_NHAN_VIEN 100

// Cấu trúc biểu diễn thông tin nhân viên
typedef struct {
    int maNV;
    char hoTen[50];
    float luongCoBan;
    int phutMuon;
    float soGioOT;
} NhanVien;

// Khai báo nguyên mẫu hàm (Function Prototypes)
void xoaBoNhoDem();
void hienThiMenu();
int timKiemTheoMa(NhanVien ds[], int n, int ma);
void hienThiDanhSach(NhanVien ds[], int n);
int themNhanVien(NhanVien ds[], int *n);
void suaNhanVien(NhanVien ds[], int n);
int xoaNhanVien(NhanVien ds[], int *n);

int main() {
    NhanVien ds[MAX_NHAN_VIEN];
    int soLuong = 0;
    int choice;

    do {
        hienThiMenu();
        printf("Nhap lua chon: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("=> Loi: Lua chon khong hop le!\n");
            xoaBoNhoDem();
            continue;
        }
        xoaBoNhoDem(); // Xóa ký tự xuống dòng thừa sau khi nhập số

        switch (choice) {
            case 1:
                hienThiDanhSach(ds, soLuong);
                break;
            case 2:
                soLuong = themNhanVien(ds, &soLuong);
                break;
            case 3:
                suaNhanVien(ds, soLuong);
                break;
            case 4:
                soLuong = xoaNhanVien(ds, &soLuong);
                break;
            case 0:
                printf("=> Thoat chuong trinh. Tam biet!\n");
                break;
            default:
                printf("=> Loi: Lua chon khong hop le! Vui long chon tu 0 den 4.\n");
        }
    } while (choice != 0);

    return 0;
}

// Hàm xóa bộ nhớ đệm để tránh trôi lệnh khi dùng xen kẽ scanf và fgets
void xoaBoNhoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Hiển thị giao diện menu Terminal
void hienThiMenu() {
    printf("\n===== HE THONG QUAN LY NHAN SU HRM =====\n");
    printf("1. Xem danh sach nhan vien & Bang luong\n");
    printf("2. Them nhan vien moi\n");
    printf("3. Cap nhat thong tin nhan vien\n");
    printf("4. Xoa nhan vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
}

// Tìm kiếm nhân viên theo mã, trả về index nếu thấy, ngược lại trả về -1
int timKiemTheoMa(NhanVien ds[], int n, int ma) {
    for (int i = 0; i < n; i++) {
        if (ds[i].maNV == ma) {
            return i;
        }
    }
    return -1;
}

// Hiển thị danh sách nhân viên và bảng lương chi tiết
void hienThiDanhSach(NhanVien ds[], int n) {
    if (n == 0) {
        printf("\n=> Danh sach nhan vien trong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");
    for (int i = 0; i < n; i++) {
        float tienPhat = (ds[i].phutMuon > 15) ? 50000.0f : 0.0f;
        float tienOT = ds[i].soGioOT * (ds[i].luongCoBan / 160.0f) * 1.5f;
        float luongThucNhan = ds[i].luongCoBan + tienOT - tienPhat;

        printf("Ma NV: %d\n", ds[i].maNV);
        printf("Ho ten: %s\n", ds[i].hoTen);
        printf("Luong co ban: %.0f\n", ds[i].luongCoBan);
        printf("Phut muon: %d\n", ds[i].phutMuon);
        printf("Gio OT: %.1f\n", ds[i].soGioOT);
        printf("Tien phat: %.0f\n", tienPhat);
        printf("Tien OT: %.0f\n", tienOT);
        printf("Luong thuc nhan: %.0f\n", luongThucNhan);
        if (i < n - 1) {
            printf("---------------------------\n");
        }
    }
    printf("\nTong so nhan vien: %d\n", n);
}

// Thêm nhân viên mới vào danh sách
int themNhanVien(NhanVien ds[], int *n) {
    if (*n >= MAX_NHAN_VIEN) {
        printf("\n=> Loi: Danh sach da day (toi da %d nhan vien)!\n", MAX_NHAN_VIEN);
        return *n;
    }

    NhanVien nv;
    printf("\n--- THEM NHAN VIEN ---\n");
    
    printf("Ma NV: ");
    while (scanf("%d", &nv.maNV) != 1 || nv.maNV <= 0) {
        printf("Loi: Ma NV phai la so nguyen duong. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    // Kiểm tra trùng mã nhân viên
    if (timKiemTheoMa(ds, *n, nv.maNV) != -1) {
        printf("\n=> Loi: Ma nhan vien da ton tai!\n");
        return *n;
    }

    printf("Ho ten: ");
    fgets(nv.hoTen, sizeof(nv.hoTen), stdin);
    nv.hoTen[strcspn(nv.hoTen, "\n")] = 0; // Xóa ký tự xuống dòng '\n'

    printf("Luong co ban: ");
    while (scanf("%f", &nv.luongCoBan) != 1 || nv.luongCoBan < 0) {
        printf("Loi: Luong co ban khong duoc am. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    printf("Phut di muon: ");
    while (scanf("%d", &nv.phutMuon) != 1 || nv.phutMuon < 0) {
        printf("Loi: Phut di muon khong duoc am. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    printf("So gio OT: ");
    while (scanf("%f", &nv.soGioOT) != 1 || nv.soGioOT < 0) {
        printf("Loi: So gio OT khong duoc am. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    ds[*n] = nv;
    (*n)++;
    printf("\n=> Them nhan vien thanh cong!\n");
    return *n;
}

// Cập nhật thông tin (Lương, phút muộn, giờ OT) của nhân viên
void suaNhanVien(NhanVien ds[], int n) {
    if (n == 0) {
        printf("\n=> Danh sach nhan vien trong!\n");
        return;
    }

    int ma;
    printf("\n--- CAP NHAT THONG TIN NHAN VIEN ---\n");
    printf("Nhap ma NV can sua: ");
    while (scanf("%d", &ma) != 1) {
        printf("Loi: Ma khong hop le. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    int index = timKiemTheoMa(ds, n, ma);
    if (index == -1) {
        printf("\n=> Loi: Khong tim thay nhan vien co ma %d!\n", ma);
        return;
    }

    printf("Tim thay nhan vien: %s\n", ds[index].hoTen);
    
    printf("Nhap luong co ban moi: ");
    while (scanf("%f", &ds[index].luongCoBan) != 1 || ds[index].luongCoBan < 0) {
        printf("Loi: Luong khong duoc am. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    printf("Nhap phut di muon moi: ");
    while (scanf("%d", &ds[index].phutMuon) != 1 || ds[index].phutMuon < 0) {
        printf("Loi: Phut muon khong duoc am. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    printf("Nhap so gio OT moi: ");
    while (scanf("%f", &ds[index].soGioOT) != 1 || ds[index].soGioOT < 0) {
        printf("Loi: Gio OT khong duoc am. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    printf("\n=> Cap nhat thong tin thanh cong!\n");
}

// Xóa nhân viên và dịch chuyển mảng
int xoaNhanVien(NhanVien ds[], int *n) {
    if (*n == 0) {
        printf("\n=> Danh sach nhan vien trong!\n");
        return *n;
    }

    int ma;
    printf("\n--- XOA NHAN VIEN ---\n");
    printf("Ma NV can xoa: ");
    while (scanf("%d", &ma) != 1) {
        printf("Loi: Ma khong hop le. Nhap lai: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    int index = timKiemTheoMa(ds, *n, ma);
    if (index == -1) {
        printf("\n=> Loi: Khong tim thay nhan vien!\n");
        return *n;
    }

    // Dịch chuyển các phần tử phía sau lên 1 vị trí
    for (int i = index; i < *n - 1; i++) {
        ds[i] = ds[i + 1];
    }
    (*n)--;

    printf("\n=> Xoa nhan vien thanh cong!\n");
    return *n;
}