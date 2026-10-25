#include <stdio.h>
#include <string.h>

#define MAX_NV 50

// Khai báo cấu trúc Nhân Viên
typedef struct {
    int maNV;
    char hoTen[50];
    int soPhutDiMuon;
    float luongCoBan;
} NhanVien;

// Khai báo nguyên mẫu hàm (Function Prototypes)
void xoaBoNhoDem();
int timTheoMaNV(NhanVien ds[], int n, int ma);
int themNhanVien(NhanVien ds[], int *n);
void hienThiDanhSach(NhanVien ds[], int n);
void capNhatPhutDiMuon(NhanVien ds[], int n);
void timKiemNhanVien(NhanVien ds[], int n);

int main() {
    NhanVien ds[MAX_NV];
    int soLuong = 0;
    int choice;

    do {
        printf("\n===== HỆ THỐNG QUẢN LÝ CHẤM CÔNG HRM =====\n");
        printf("1. Thêm nhân viên mới\n");
        printf("2. Hiển thị danh sách và tính lương\n");
        printf("3. Cập nhật số phút đi muộn\n");
        printf("4. Tìm kiếm nhân viên theo mã\n");
        printf("0. Thoát\n");
        printf("==========================================\n");
        printf("Nhập lựa chọn: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("=> Lựa chọn không hợp lệ!\n");
            xoaBoNhoDem();
            continue;
        }
        xoaBoNhoDem(); // Xóa bộ nhớ đệm sau khi đọc số từ menu

        switch (choice) {
            case 1:
                soLuong = themNhanVien(ds, &soLuong);
                break;
            case 2:
                hienThiDanhSach(ds, soLuong);
                break;
            case 3:
                capNhatPhutDiMuon(ds, soLuong);
                break;
            case 4:
                timKiemNhanVien(ds, soLuong);
                break;
            case 0:
                printf("=> Thoát chương trình. Tạm biệt!\n");
                break;
            default:
                printf("=> Lựa chọn không hợp lệ! Vui lòng chọn từ 0 đến 4.\n");
        }
    } while (choice != 0);

    return 0;
}

// Hàm xóa bộ nhớ đệm để tránh lỗi trôi lệnh khi dùng xen kẽ scanf và fgets
void xoaBoNhoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Hàm tìm nhân viên theo mã, trả về vị trí (index) nếu tìm thấy, hoặc -1 nếu không
int timTheoMaNV(NhanVien ds[], int n, int ma) {
    for (int i = 0; i < n; i++) {
        if (ds[i].maNV == ma) {
            return i;
        }
    }
    return -1;
}

// Hàm thêm nhân viên mới
int themNhanVien(NhanVien ds[], int *n) {
    if (*n >= MAX_NV) {
        printf("=> Danh sách nhân viên đã đầy (tối đa %d)!\n", MAX_NV);
        return *n;
    }

    NhanVien nv;
    printf("Nhập mã nhân viên: ");
    while (scanf("%d", &nv.maNV) != 1 || nv.maNV <= 0) {
        printf("Mã nhân viên không hợp lệ. Nhập lại: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    // Kiểm tra trùng mã nhân viên
    if (timTheoMaNV(ds, *n, nv.maNV) != -1) {
        printf("=> Lỗi: Mã nhân viên %d đã tồn tại trong hệ thống!\n", nv.maNV);
        return *n;
    }

    printf("Nhập họ và tên: ");
    fgets(nv.hoTen, sizeof(nv.hoTen), stdin);
    nv.hoTen[strcspn(nv.hoTen, "\n")] = 0; // Xóa ký tự xuống dòng '\n' do fgets để lại

    printf("Nhập số phút đi muộn: ");
    while (scanf("%d", &nv.soPhutDiMuon) != 1 || nv.soPhutDiMuon < 0) {
        printf("Số phút đi muộn không hợp lệ (>= 0). Nhập lại: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    printf("Nhập lương cơ bản: ");
    while (scanf("%f", &nv.luongCoBan) != 1 || nv.luongCoBan < 0) {
        printf("Lương cơ bản không hợp lệ (>= 0). Nhập lại: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    ds[*n] = nv;
    (*n)++;
    printf("=> Thêm nhân viên thành công!\n");
    return *n;
}

// Hàm hiển thị danh sách nhân viên và tính lương thực nhận
void hienThiDanhSach(NhanVien ds[], int n) {
    if (n == 0) {
        printf("=> Danh sách nhân viên trống!\n");
        return;
    }

    printf("\n--- DANH SÁCH NHÂN VIÊN ---\n");
    printf("%-6s | %-20s | %-10s | %-15s\n", "Ma NV", "Ho ten", "Phut muon", "Luong thuc nhan");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int tienPhat = (ds[i].soPhutDiMuon > 15) ? 50000 : 0;
        float luongThucNhan = ds[i].luongCoBan - tienPhat;
        printf("%-6d | %-20s | %-10d | %.0f\n", 
               ds[i].maNV, ds[i].hoTen, ds[i].soPhutDiMuon, luongThucNhan);
    }
    printf("---------------------------------------------------------------\n");
}

// Hàm cập nhật số phút đi muộn
void capNhatPhutDiMuon(NhanVien ds[], int n) {
    if (n == 0) {
        printf("=> Danh sách nhân viên trống!\n");
        return;
    }

    int ma;
    printf("Nhập mã NV cần cập nhật: ");
    while (scanf("%d", &ma) != 1) {
        printf("Mã không hợp lệ. Nhập lại: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    int viTri = timTheoMaNV(ds, n, ma);
    if (viTri == -1) {
        printf("=> Không tìm thấy nhân viên!\n");
        return;
    }

    int phutMoi;
    printf("Nhập số phút đi muộn mới: ");
    while (scanf("%d", &phutMoi) != 1 || phutMoi < 0) {
        printf("Số phút đi muộn không hợp lệ (>= 0). Nhập lại: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    ds[viTri].soPhutDiMuon = phutMoi;
    printf("=> Cập nhật thành công!\n");
}

// Hàm tìm kiếm và hiển thị chi tiết thông tin nhân viên
void timKiemNhanVien(NhanVien ds[], int n) {
    if (n == 0) {
        printf("=> Danh sách nhân viên trống!\n");
        return;
    }

    int ma;
    printf("Nhập mã NV cần tìm: ");
    while (scanf("%d", &ma) != 1) {
        printf("Mã không hợp lệ. Nhập lại: ");
        xoaBoNhoDem();
    }
    xoaBoNhoDem();

    int viTri = timTheoMaNV(ds, n, ma);
    if (viTri == -1) {
        printf("=> Không tìm thấy nhân viên có mã %d!\n", ma);
        return;
    }

    int tienPhat = (ds[viTri].soPhutDiMuon > 15) ? 50000 : 0;
    float luongThucNhan = ds[viTri].luongCoBan - tienPhat;

    printf("\n--- THÔNG TIN CHI TIẾT NHÂN VIÊN ---\n");
    printf("Mã NV           : %d\n", ds[viTri].maNV);
    printf("Họ tên          : %s\n", ds[viTri].hoTen);
    printf("Số phút đi muộn : %d\n", ds[viTri].soPhutDiMuon);
    printf("Lương cơ bản    : %.0f VNĐ\n", ds[viTri].luongCoBan);
    printf("Tiền phạt       : %d VNĐ\n", tienPhat);
    printf("Lương thực nhận : %.0f VNĐ\n", luongThucNhan);
}